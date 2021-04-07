//
// Created by Vitaliy on 10/30/20.
//
#include <iostream>
#include <mpi.h>
#include <exception>

auto getVector(const uint64_t n) {
    auto vector = new float [n];

    for (int i = 0; i < n; ++i) {
        vector[i] = random() / MAXFLOAT;
    }

    return vector;
}

auto getMatrix(const uint64_t n) {
    auto matrix = new float [n*n];
    for (int i = 0; i < n*n; ++i) {
        matrix[i] = random() / MAXFLOAT;
    }

    return matrix;
}

/**
 * W=32
     Median of time taken by function: 6535 nanoseconds
   W=64
     Median of time taken by function: 23437 nanoseconds
 * @param n
 */
void testMatrixVectorMultSerial(const float* matrix,
                                const float* vIn,
                                float* vOut,
                                const uint64_t n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            vOut[j] += matrix[i*n + j] * vIn[j];
        }
    }
}

// loop unrolling (ptr over int indexes)
// clang optimizations
void rowMatrixVectorMultTask(const float* m,
                             float* vOut,
                             const float* vIn,
                             const int64_t rowFrom,
                             const int64_t rowTo,
                             const int64_t n) {
    for (int rowId = rowFrom; rowId < rowTo; ++rowId) {
        for (int i = 0; i < n; ++i) {
            vOut[i] += m[rowId*n + i] * vIn[i];
        }
    }
}

void rowMatrixVectorMultLoopUnrollingTask(const float* m,
                             float* vOut,
                             const float* vIn,
                             const int64_t rowFrom,
                             const int64_t rowTo,
                             const int64_t n) {
    for (int rowId = rowFrom; rowId < rowTo; ++rowId) {
        for (int i = 0; i+8 < n; i += 8) {
            vOut[i] += m[rowId * n + i] * vIn[i];
            vOut[i + 1] += m[rowId * n + i + 1] * vIn[i + 1];
            vOut[i + 2] += m[rowId * n + i + 2] * vIn[i + 2];
            vOut[i + 3] += m[rowId * n + i + 3] * vIn[i + 3];
            vOut[i + 4] += m[rowId * n + i + 4] * vIn[i + 4];
            vOut[i + 5] += m[rowId * n + i + 5] * vIn[i + 5];
            vOut[i + 6] += m[rowId * n + i + 6] * vIn[i + 6];
            vOut[i + 7] += m[rowId * n + i + 7] * vIn[i + 7];
        }
    }
}

void testMatrixVectorMultParallelStriped(float* matrix,
                                         const float* vIn,
                                         float* vOut,
                                         const uint64_t n,
                                         const uint8_t threadsCount) {
    uint64_t batchSize = n / threadsCount;
    std::vector<std::thread> v;
    for (int i = 0; i < threadsCount; ++i) {
        std::thread t{rowMatrixVectorMultTask, matrix, vOut, vIn, i * batchSize, (i + 1) * batchSize, n};
        v.push_back(move(t));
    }
    for_each(v.begin(), v.end(), [](std::thread &t){
        t.join();
    });
}

void testMatrixVectorMultParallelStripedLoopUnrolling(float* matrix,
                                         const float* vIn,
                                         float* vOut,
                                         const uint64_t n,
                                         const uint8_t threadsCount) {
    uint64_t batchSize = n / threadsCount;
    std::vector<std::thread> v;
    for (int i = 0; i < threadsCount; ++i) {
        std::thread t{rowMatrixVectorMultLoopUnrollingTask, matrix, vOut, vIn, i * batchSize, (i + 1) * batchSize, n};
        v.push_back(move(t));
    }
    for_each(v.begin(), v.end(), [](std::thread &t){
        t.join();
    });
}

// Data distribution among the processes
void DataDistribution(const float* pMatrix,
                      float* pProcRows,
                      float* vIn,
                      const uint64_t n,
                      int RowNum,
                      int ProcNum,
                      int ProcRank) {
    int *pSendNum; // the number of elements sent to the process
    int *pSendInd; // the index of the first data element sent to the process
    int RestRows = n; // Number of rows, that haven’t been distributed yet

    //Broadcast input Vector to every processors.
    MPI_Bcast(vIn, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Alloc memory for temporary objects
    pSendInd = new int [ProcNum];
    pSendNum = new int [ProcNum];

    // Define the disposition of the matrix rows for current process
    RowNum = (n/ProcNum);
    pSendNum[0] = RowNum*n;
    pSendInd[0] = 0;
    for (int i=1; i<ProcNum; i++) {
        RestRows -= RowNum;
        RowNum = RestRows/(ProcNum-i);
        pSendNum[i] = RowNum*n;
        pSendInd[i] = pSendInd[i-1]+pSendNum[i-1];
    }
    // Scatter the rows
    MPI_Scatterv(pMatrix , pSendNum, pSendInd, MPI_FLOAT, pProcRows,
                 pSendNum[ProcRank], MPI_FLOAT, 0, MPI_COMM_WORLD);
    // Free the memory
    delete [] pSendNum;
    delete [] pSendInd;
}

void ParallelResultCalculation(const float* pProcRows,
                               const float* pVector,
                               float* pProcResult,
                               const uint64_t Size,
                               int RowNum) {
    for (int i=0; i<RowNum; i++) {
        pProcResult[i] = 0;
        for (int j=0; j<Size; j++)
            pProcResult[i] += pProcRows[i*Size+j]*pVector[j];
    }
}

// Function for gathering the result vector
void ResultReplication(float* pProcResult,
                       float* pResult,
                       const uint64_t Size,
                       int ProcNum,
                       int ProcRank) {
    int i; // Loop variable
    int *pReceiveNum; // Number of elements, that current process sends
    int *pReceiveInd; /* Index of the first element from current process
in result vector */
    int RestRows=Size; // Number of rows, that haven’t been distributed yet
//Alloc memory for temporary objects
    pReceiveNum = new int [ProcNum];
    pReceiveInd = new int [ProcNum];
//Define the disposition of the result vector block of current processor
    pReceiveInd[0] = 0;
    pReceiveNum[0] = Size/ProcNum;
    for (i=1; i<ProcNum; i++) {
        RestRows -= pReceiveNum[i-1];
        pReceiveNum[i] = RestRows/(ProcNum-i);
        pReceiveInd[i] = pReceiveInd[i-1]+pReceiveNum[i-1];
    }
//Gather the whole result vector on every processor
    MPI_Allgatherv(pProcResult, pReceiveNum[ProcRank], MPI_DOUBLE, pResult,
                   pReceiveNum, pReceiveInd, MPI_DOUBLE, MPI_COMM_WORLD);
//Free the memory
    delete [] pReceiveNum;
    delete [] pReceiveInd;
}

void testMatrixVectorMultMPIParallelHorizontalStriped(const float* matrix,
                                                      float* vIn,
                                                      float* vOut,
                                                      const uint64_t n,
                                                      int ProcNum) {

    char **args[] = {
            (char**)"-n",
            (char**)"10",
            NULL
    };
    int argc = 2;
    int ProcRank;
    float* pProcRows;
    float* pProcResult;
    int RowNum;
    MPI_Init(&argc, args);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    DataDistribution(matrix, pProcRows, vIn, n, RowNum, ProcNum, ProcRank);
    ParallelResultCalculation(pProcRows, vIn, pProcResult, n, RowNum);
    ResultReplication(pProcResult, vOut, n, ProcNum, ProcRank);
    MPI_Finalize();
}

void verifyVectors(const float* expected, const float* actual, const uint64_t n) {
    for (int i = 0; i < n; ++i) {
        if (expected[i] != actual[i])
            std::cout << "error in index " << i << " expected=" << expected[i] << " actual=" << actual[i] << " diff=" << (expected[i]-actual[i]) << "\n";
    }
}

void verifyMatrices(const float* expected, const float* actual, const uint64_t n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (expected[i*n+j] != actual[i*n+j])
                std::cout << "error in index " << i << " expected=" << expected[i*n+j] << " actual=" << actual[i*n+j]
                          << " diff="
                          << (expected[i*n+j] - actual[i*n+j]) << "\n";
        }
    }
}

void testMatrixVectorMult() {
    uint8_t iterations = 11;
    uint8_t threadsCount = 16;
    auto W = new int[iterations];
    W[0] = 32;
    uint8_t q = 2;
    for (int i = 1; i < iterations; ++i) {
        W[i] = W[i-1] * q;
    }

    for (int i = 0; i < iterations; ++i) {
        auto matrix = getMatrix(W[i]);
        auto vIn = getVector(W[i]);
        auto vOutSerial = new float [W[i]];

        std::cout << "\nIteration " << i << "\n";
        std::cout << "W=" << W[i] * W[i] << "\n";
        std::cout << "Ts:\n";
        measure([&W, &matrix, &vIn, &vOutSerial, i] {
            testMatrixVectorMultSerial(matrix, vIn, vOutSerial, W[i]);
        }, 1, "seconds", "nonverbose");

        std::cout << "\nTp:\n";
        auto vOutParallelStriped = new float [W[i]];
        auto matrixIn = new float [W[i]*W[i]];
        std::copy(matrix, matrix + W[i]*W[i], matrixIn);
        measure([&W, &matrixIn, &vIn, &vOutParallelStriped, threadsCount, i] {
            testMatrixVectorMultParallelStriped(matrixIn, vIn, vOutParallelStriped, W[i], threadsCount);
        }, 1, "seconds", "nonverbose");
        verifyVectors(vOutSerial, vOutParallelStriped, W[i]);

        std::cout << "\nTp loop unrolling:\n";
        auto vOutParallelStripedLoopUnrolling = new float [W[i]];
        auto matrixInLoopUnrolling = new float [W[i]*W[i]];
        std::copy(matrix, matrix + W[i]*W[i], matrixInLoopUnrolling);
        measure([&W, &matrixInLoopUnrolling, &vIn, &vOutParallelStripedLoopUnrolling, threadsCount, i] {
            testMatrixVectorMultParallelStripedLoopUnrolling(matrixInLoopUnrolling, vIn, vOutParallelStripedLoopUnrolling, W[i], threadsCount);
        }, 1, "seconds", "nonverbose");
        verifyVectors(vOutSerial, vOutParallelStripedLoopUnrolling, W[i]);

//        std::cout << "\nTpMPI:\n";
//        auto vOutParallelMPIStriped = new float [W[i]];
//        auto matrixInMPI = new float [W[i]*W[i]];
//        std::copy(matrix, matrix + W[i]*W[i], matrixInMPI);
//        measure([&W, &matrixInMPI, &vIn, &vOutParallelMPIStriped, threadsCount, i] {
//            testMatrixVectorMultMPIParallelHorizontalStriped(matrixInMPI, vIn, vOutParallelMPIStriped, W[i], threadsCount);
//        }, 1, "seconds", "nonverbose");
//        verifyVectors(vOutSerial, vOutParallelMPIStriped, W[i]);

        delete [] matrix;
        delete [] vIn;
        delete [] vOutSerial;
        delete [] matrixIn;
        delete [] vOutParallelStriped;
        delete [] matrixInLoopUnrolling;
        delete [] vOutParallelStripedLoopUnrolling;
//        delete [] matrixInMPI;
//        delete [] vOutParallelMPIStriped;
    }
}

void testMatrixMatrixMultSerial(const float* matrix1,
                                const float* matrix2,
                                float* mOut,
                                const uint64_t n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                mOut[i * n + j] += matrix1[i * n + k] * matrix2[k * n + j];
            }
        }
    }
}

void rowMatrixMatrixMultHorizontalTask(const float* matrix1,
                                       const float* matrix2,
                                       float* mOut,
                                       const int64_t rowFrom,
                                       const int64_t rowTo,
                                       const int64_t n) {
    for (int rowId = rowFrom; rowId < rowTo; ++rowId) {
        for (int i = 0; i < n; ++i) {
            for (int k = 0; k < n; ++k) {
                mOut[rowId * n + i] += matrix1[rowId * n + k] * matrix2[k * n + i];
            }
        }
    }
}

void rowMatrixMatrixMultHorizontalLoopUnrolledTask(const float* matrix1,
                                       const float* matrix2,
                                       float* mOut,
                                       const int64_t rowFrom,
                                       const int64_t rowTo,
                                       const int64_t n) {
    for (int rowId = rowFrom; rowId < rowTo; ++rowId) {
        for (int i = 0; i < n; ++i) {
            for (int k = 0; k+8 < n; k+=8) {
                mOut[rowId * n + i] += matrix1[rowId * n + k] * matrix2[k * n + i];
                mOut[rowId * n + i] += matrix1[rowId * n + k + 1] * matrix2[(k+1) * n + i];
                mOut[rowId * n + i] += matrix1[rowId * n + k + 2] * matrix2[(k+2) * n + i];
                mOut[rowId * n + i] += matrix1[rowId * n + k + 3] * matrix2[(k+3) * n + i];
                mOut[rowId * n + i] += matrix1[rowId * n + k + 4] * matrix2[(k+4) * n + i];
                mOut[rowId * n + i] += matrix1[rowId * n + k + 5] * matrix2[(k+5) * n + i];
                mOut[rowId * n + i] += matrix1[rowId * n + k + 6] * matrix2[(k+6) * n + i];
                mOut[rowId * n + i] += matrix1[rowId * n + k + 7] * matrix2[(k+7) * n + i];
            }
        }
    }
}

void testMatrixMatrixMultParallelStriped(const float* matrix1,
                                         const float* matrix2,
                                         float* mOut,
                                         const uint64_t n,
                                         const uint8_t threadsCount) {
    uint64_t batchSize = n / threadsCount;
    std::vector<std::thread> v;
    for (int i = 0; i < threadsCount; ++i) {
        std::thread t{rowMatrixMatrixMultHorizontalTask, matrix1, matrix2, mOut, i * batchSize, (i + 1) * batchSize, n};
        v.push_back(move(t));
    }
    for_each(v.begin(), v.end(), [](std::thread &t){
        t.join();
    });
}

void testMatrixMatrixMultParallelStripedLoopUnrolled(const float* matrix1,
                                         const float* matrix2,
                                         float* mOut,
                                         const uint64_t n,
                                         const uint8_t threadsCount) {
    uint64_t batchSize = n / threadsCount;
    std::vector<std::thread> v;
    for (int i = 0; i < threadsCount; ++i) {
        std::thread t{rowMatrixMatrixMultHorizontalLoopUnrolledTask, matrix1, matrix2, mOut, i * batchSize, (i + 1) * batchSize, n};
        v.push_back(move(t));
    }
    for_each(v.begin(), v.end(), [](std::thread &t){
        t.join();
    });
}

void testMatrixMatrixMult() {
    uint8_t iterations = 7;
    uint8_t threadsCount = 8;
    auto W = new int[iterations];
    W[0] = 32;
    uint8_t q = 2;
    for (int i = 1; i < iterations; ++i) {
        W[i] = W[i-1] * q;
    }

    for (int i = 0; i < iterations; ++i) {
        auto matrix1 = getMatrix(W[i]);
        auto matrix2 = getMatrix(W[i]);
        auto mOutSerial = new float [W[i]*W[i]];

        std::cout << "\nIteration " << i << "\n";
        std::cout << "W=" << W[i] * W[i] << "\n";
        std::cout << "Ts:\n";
        measure([&W, &matrix1, &matrix2, &mOutSerial, i] {
            testMatrixMatrixMultSerial(matrix1, matrix2, mOutSerial, W[i]);
        }, 1, "seconds", "nonverbose");

        std::cout << "\nTp:\n";
        auto mOutParallelStriped = new float [W[i]*W[i]];
        auto matrix1In = new float [W[i]*W[i]];
        auto matrix2In = new float [W[i]*W[i]];
        std::copy(matrix1, matrix1 + W[i]*W[i], matrix1In);
        std::copy(matrix2, matrix2 + W[i]*W[i], matrix2In);
        measure([&W, &matrix1In, &matrix2In, &mOutParallelStriped, threadsCount, i] {
            testMatrixMatrixMultParallelStriped(matrix1In, matrix2In, mOutParallelStriped, W[i], threadsCount);
        }, 1, "seconds", "nonverbose");
        verifyMatrices(mOutSerial, mOutParallelStriped, W[i]);

        std::cout << "\nTp loop unrolled:\n";
        auto mOutParallelStripedLoopUnrolled = new float [W[i]*W[i]];
        auto matrix1InLoopUnrolled = new float [W[i]*W[i]];
        auto matrix2InLoopUnrolled = new float [W[i]*W[i]];
        std::copy(matrix1, matrix1 + W[i]*W[i], matrix1InLoopUnrolled);
        std::copy(matrix2, matrix2 + W[i]*W[i], matrix2InLoopUnrolled);
        measure([&W, &matrix1InLoopUnrolled, &matrix2InLoopUnrolled, &mOutParallelStripedLoopUnrolled, threadsCount, i] {
            testMatrixMatrixMultParallelStripedLoopUnrolled(matrix1InLoopUnrolled, matrix2InLoopUnrolled, mOutParallelStripedLoopUnrolled, W[i], threadsCount);
        }, 1, "seconds", "nonverbose");
        verifyMatrices(mOutSerial, mOutParallelStripedLoopUnrolled, W[i]);

        delete [] matrix1;
        delete [] matrix2;
        delete [] mOutSerial;
        delete [] matrix1In;
        delete [] matrix2In;
        delete [] mOutParallelStriped;
        delete [] matrix1InLoopUnrolled;
        delete [] matrix2InLoopUnrolled;
        delete [] mOutParallelStripedLoopUnrolled;
    }
}
