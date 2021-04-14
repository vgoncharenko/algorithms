//
// Created by Vitaliy on 10/30/20.
//
#include <iostream>
#include <mpi.h>
#include <exception>

std::basic_string<char, std::char_traits<char>, std::allocator<char>> getMutexMapKey(uint64_t row, uint64_t col);

std::basic_string<char, std::char_traits<char>, std::allocator<char>> getIdxKey(const std::pair<int, int> &Idx);

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
        matrix[i] = random() / 1000000000.0f;
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

template<typename T>
void verifyMatrices(const float* expected, const T& actual, const uint64_t n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (expected[i*n+j] != actual[i*n+j])
                std::cout << "error in index [" << i << "]" << "[" << j << "] expected=" << expected[i*n+j] << " actual=" << actual[i*n+j]
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
            for (int k = 0; k+8-1 < n; k+=8) {
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

void rowMatrixMatrixMultHorizontalTrueHorizontalTask(const float* matrix1,
                                       const float* matrix2,
                                       float* mOut,
                                       const int64_t rowFrom,
                                       const int64_t rowTo,
                                       const int64_t n) {
    for (int rowId = rowFrom; rowId < rowTo; ++rowId) {
        for (int i = 0; i < n; ++i) {
            for (int k = 0; k < n; ++k) {
                mOut[rowId * n + k] += matrix1[rowId * n + i] * matrix2[i * n + k];
            }
        }
    }
}

void rowMatrixMatrixMultHorizontalTrueHorizontalLoopUnrolledTask(const float* matrix1,
                                                                 const float* matrix2,
                                                                 float* mOut,
                                                                 const int64_t rowFrom,
                                                                 const int64_t rowTo,
                                                                 const int64_t n) {
    for (int rowId = rowFrom; rowId < rowTo; ++rowId) {
        for (int i = 0; i < n; ++i) {
            for (int k = 0; k+8-1 < n; k+=8) {
                mOut[rowId * n + k] += matrix1[rowId * n + i] * matrix2[i * n + k];
                mOut[rowId * n + k+1] += matrix1[rowId * n + i] * matrix2[i * n + k+1];
                mOut[rowId * n + k+2] += matrix1[rowId * n + i] * matrix2[i * n + k+2];
                mOut[rowId * n + k+3] += matrix1[rowId * n + i] * matrix2[i * n + k+3];
                mOut[rowId * n + k+4] += matrix1[rowId * n + i] * matrix2[i * n + k+4];
                mOut[rowId * n + k+5] += matrix1[rowId * n + i] * matrix2[i * n + k+5];
                mOut[rowId * n + k+6] += matrix1[rowId * n + i] * matrix2[i * n + k+6];
                mOut[rowId * n + k+7] += matrix1[rowId * n + i] * matrix2[i * n + k+7];
            }
        }
    }
}

void rowMatrixMatrixMultCannonTask(const float* matrix1,
                                   const float* matrix2,
                                   float* mOut,
                                   const int64_t m1ColFrom,
                                   const int64_t m2RowFrom,
                                   const int64_t outRowFrom,
                                   const int64_t outColFrom,
                                   const int64_t batchSize,
                                   const int64_t n) {
    for (int y = outRowFrom; y < outRowFrom + batchSize; ++y) {
            for (int i = 0; i < batchSize; ++i) {
                for (int k = outColFrom; k+8-1 < outColFrom + batchSize; k+=8) {
                    mOut[y * n + k] += matrix1[y * n + m1ColFrom + i] * matrix2[(m2RowFrom+i) * n + k];
                    mOut[y * n + k+1] += matrix1[y * n + m1ColFrom + i] * matrix2[(m2RowFrom+i) * n + k+1];
                    mOut[y * n + k+2] += matrix1[y * n + m1ColFrom + i] * matrix2[(m2RowFrom+i) * n + k+2];
                    mOut[y * n + k+3] += matrix1[y * n + m1ColFrom + i] * matrix2[(m2RowFrom+i) * n + k+3];
                    mOut[y * n + k+4] += matrix1[y * n + m1ColFrom + i] * matrix2[(m2RowFrom+i) * n + k+4];
                    mOut[y * n + k+5] += matrix1[y * n + m1ColFrom + i] * matrix2[(m2RowFrom+i) * n + k+5];
                    mOut[y * n + k+6] += matrix1[y * n + m1ColFrom + i] * matrix2[(m2RowFrom+i) * n + k+6];
                    mOut[y * n + k+7] += matrix1[y * n + m1ColFrom + i] * matrix2[(m2RowFrom+i) * n + k+7];
                }
            }
    }
}

std::string getIdxKey(const uint64_t i, const uint64_t j) { return std::to_string(i) + '_' + std::to_string(j); }

struct MatrixBlock {
public:
    mutable std::mutex mut;
    std::condition_variable blockIsFree;
    bool blockIsFreeFlag = false;
};

void rowMatrixMatrixMultCannonCondVarTask(const float* matrix1,
                                          const float* matrix2,
                                          float* mOut,
                                          const std::unordered_map<std::string, MatrixBlock*> &m1Map,
                                          const std::unordered_map<std::string, MatrixBlock*> &m2Map,
                                          int64_t m1ColFrom,
                                          int64_t m2RowFrom,
                                          const int64_t outRowFrom,
                                          const int64_t outColFrom,
                                          const int64_t batchSize,
                                          const int64_t n,
                                          const int64_t blockCount) {
    uint64_t it = 0;
    while (it < blockCount) {
        for (int64_t y = outRowFrom*batchSize; y < outRowFrom*batchSize + batchSize; ++y) {
            for (int i = 0; i < batchSize; ++i) {
                for (int64_t k = outColFrom*batchSize; k + 8 - 1 < outColFrom*batchSize + batchSize; k += 8) {
                    mOut[y * n + k] += matrix1[y * n + m1ColFrom*batchSize + i] * matrix2[(m2RowFrom*batchSize + i) * n + k];
                    mOut[y * n + k + 1] += matrix1[y * n + m1ColFrom*batchSize + i] * matrix2[(m2RowFrom*batchSize + i) * n + k + 1];
                    mOut[y * n + k + 2] += matrix1[y * n + m1ColFrom*batchSize + i] * matrix2[(m2RowFrom*batchSize + i) * n + k + 2];
                    mOut[y * n + k + 3] += matrix1[y * n + m1ColFrom*batchSize + i] * matrix2[(m2RowFrom*batchSize + i) * n + k + 3];
                    mOut[y * n + k + 4] += matrix1[y * n + m1ColFrom*batchSize + i] * matrix2[(m2RowFrom*batchSize + i) * n + k + 4];
                    mOut[y * n + k + 5] += matrix1[y * n + m1ColFrom*batchSize + i] * matrix2[(m2RowFrom*batchSize + i) * n + k + 5];
                    mOut[y * n + k + 6] += matrix1[y * n + m1ColFrom*batchSize + i] * matrix2[(m2RowFrom*batchSize + i) * n + k + 6];
                    mOut[y * n + k + 7] += matrix1[y * n + m1ColFrom*batchSize + i] * matrix2[(m2RowFrom*batchSize + i) * n + k + 7];
                }
            }
        }
        auto block1 = m1Map.find(getIdxKey(outRowFrom, m1ColFrom));
        auto block2 = m2Map.find(getIdxKey(m2RowFrom, outColFrom));
        {
            std::scoped_lock lk(block1->second->mut, block2->second->mut);
            block1->second->blockIsFreeFlag = true;
            block2->second->blockIsFreeFlag = true;
        }
        block1->second->blockIsFree.notify_one();
        block2->second->blockIsFree.notify_one();

        ++it;
        m1ColFrom = (m1ColFrom + 1) % blockCount;
        m2RowFrom = (m2RowFrom + 1) % blockCount;

        auto blockM1 = m1Map.find(getIdxKey(outRowFrom, m1ColFrom));
        std::unique_lock<std::mutex> blockM1Lock(blockM1->second->mut);
        blockM1->second->blockIsFree.wait(blockM1Lock, [&blockM1] { return blockM1->second->blockIsFreeFlag; });

        auto blockM2 = m2Map.find(getIdxKey(m2RowFrom, outColFrom));
        std::unique_lock<std::mutex> blockM2Lock(blockM2->second->mut);
        blockM2->second->blockIsFree.wait(blockM2Lock, [&blockM2] { return blockM2->second->blockIsFreeFlag; });
    }
}

void rowMatrixMatrixMultHorizontalTrueHorizontalLoopUnrolledVectorTask(const std::vector<float> &matrix1,
                                                                       const std::vector<float> &matrix2,
                                                                       std::vector<float> &mOut,
                                                                       const int64_t rowFrom,
                                                                       const int64_t rowTo,
                                                                       const int64_t n) {
    for (int rowId = rowFrom; rowId < rowTo; ++rowId) {
        for (int i = 0; i < n; ++i) {
            for (int k = 0; k + 8 - 1 < n; k += 8) {
                mOut[rowId * n + k] += matrix1[rowId * n + i] * matrix2[i * n + k];
                mOut[rowId * n + k + 1] += matrix1[rowId * n + i] * matrix2[i * n + k + 1];
                mOut[rowId * n + k + 2] += matrix1[rowId * n + i] * matrix2[i * n + k + 2];
                mOut[rowId * n + k + 3] += matrix1[rowId * n + i] * matrix2[i * n + k + 3];
                mOut[rowId * n + k + 4] += matrix1[rowId * n + i] * matrix2[i * n + k + 4];
                mOut[rowId * n + k + 5] += matrix1[rowId * n + i] * matrix2[i * n + k + 5];
                mOut[rowId * n + k + 6] += matrix1[rowId * n + i] * matrix2[i * n + k + 6];
                mOut[rowId * n + k + 7] += matrix1[rowId * n + i] * matrix2[i * n + k + 7];
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

void testMatrixMatrixMultParallelStripedTrueHorizontal(const float* matrix1,
                                                       const float* matrix2,
                                                       float* mOut,
                                                       const uint64_t n,
                                                       const uint8_t threadsCount) {
    uint64_t batchSize = n / threadsCount;
    std::vector<std::thread> v;
    for (int i = 0; i < threadsCount; ++i) {
        std::thread t{rowMatrixMatrixMultHorizontalTrueHorizontalTask, matrix1, matrix2, mOut, i * batchSize, (i + 1) * batchSize, n};
        v.push_back(move(t));
    }
    for_each(v.begin(), v.end(), [](std::thread &t){
        t.join();
    });
}

void testMatrixMatrixMultParallelStripedTrueHorizontalLoopUnrolled(const float* matrix1,
                                                                   const float* matrix2,
                                                                   float* mOut,
                                                                   const uint64_t n,
                                                                   const uint8_t threadsCount) {
    uint64_t batchSize = n / threadsCount;
    std::vector<std::thread> v;
    for (int i = 0; i < threadsCount; ++i) {
        std::thread t{rowMatrixMatrixMultHorizontalTrueHorizontalLoopUnrolledTask, matrix1, matrix2, mOut, i * batchSize, (i + 1) * batchSize, n};
        v.push_back(move(t));
    }
    for_each(v.begin(), v.end(), [](std::thread &t){
        t.join();
    });
}

template<typename T>
void testMatrixMatrixMultParallelStripedTrueHorizontalLoopUnrolledVector(const std::vector<T> &matrix1,
                                                                         const std::vector<T> &matrix2,
                                                                         std::vector<T> &mOut,
                                                                         const uint64_t n,
                                                                         const uint8_t threadsCount) {
    uint64_t batchSize = n / threadsCount;
    std::vector<std::thread> v;
    for (int i = 0; i < threadsCount; ++i) {
        std::thread t{rowMatrixMatrixMultHorizontalTrueHorizontalLoopUnrolledVectorTask, std::ref(matrix1), std::ref(matrix2), std::ref(mOut), i * batchSize, (i + 1) * batchSize, n};
        v.push_back(move(t));
    }
    for_each(v.begin(), v.end(), [](std::thread &t){
        t.join();
    });
}

template<typename T>
std::vector<T> toVector(const T* matrix, const uint64_t n) {
    std::vector<T> v(n);
    for (int i = 0; i < n; ++i) {
        v[i] = matrix[i];
    }

    return v;
}

void testMatrixMatrixMultParallelCannon(const float* matrix1,
                                        const float* matrix2,
                                        float* mOut,
                                        const uint64_t n,
                                        const uint8_t threadsCount) {
    int sqrtThreadCount = ceil(sqrt(threadsCount));
    uint64_t batchSize = n / sqrtThreadCount;
    for (int k = 0; k < sqrtThreadCount; ++k) {
        std::vector<std::thread> v;
        for (int p_i = 0; p_i < sqrtThreadCount; ++p_i) {
            for (int p_j = 0; p_j < sqrtThreadCount; ++p_j) {
                std::pair<int,int> A = std::make_pair(p_i, ((p_i + p_j + k) % sqrtThreadCount));
                std::pair<int,int> B = std::make_pair(((p_i + p_j + k) % sqrtThreadCount), p_j);
                std::pair<int,int> C = std::make_pair(p_i, p_j);
                std::thread t{rowMatrixMatrixMultCannonTask, matrix1, matrix2, mOut,
                              A.second * batchSize,
                              B.first * batchSize,
                              C.first * batchSize, C.second * batchSize,
                              batchSize,
                              n};
                v.push_back(move(t));
            }
        }

        for_each(v.begin(), v.end(), [](std::thread &t) {
            t.join();
        });
    }
}

void testMatrixMatrixMultParallelCannonCondVar(const float* matrix1,
                                               const float* matrix2,
                                               float* mOut,
                                               const uint64_t n,
                                               const uint8_t threadsCount) {
    std::unordered_map<std::string, MatrixBlock*> m1Map(threadsCount);
    std::unordered_map<std::string, MatrixBlock*> m2Map(threadsCount);
    int sqrtThreadCount = ceil(sqrt(threadsCount));
    uint64_t batchSize = n / sqrtThreadCount;
    std::vector<std::thread> v;
    for (int p_i = 0; p_i < sqrtThreadCount; ++p_i) {
        for (int p_j = 0; p_j < sqrtThreadCount; ++p_j) {
            std::pair<int, int> A = std::make_pair(p_i, ((p_i + p_j) % sqrtThreadCount));
            m1Map.insert({getIdxKey(A.first, A.second), new MatrixBlock()});
            std::pair<int, int> B = std::make_pair(((p_i + p_j) % sqrtThreadCount), p_j);
            m2Map.insert({getIdxKey(B.first, B.second), new MatrixBlock()});
        }
    }
    for (int p_i = 0; p_i < sqrtThreadCount; ++p_i) {
        for (int p_j = 0; p_j < sqrtThreadCount; ++p_j) {
            std::pair<int, int> A = std::make_pair(p_i, ((p_i + p_j) % sqrtThreadCount));
            std::pair<int, int> B = std::make_pair(((p_i + p_j) % sqrtThreadCount), p_j);
            std::pair<int, int> C = std::make_pair(p_i, p_j);
            std::thread t{rowMatrixMatrixMultCannonCondVarTask, matrix1, matrix2, mOut,
                          std::ref(m1Map),
                          std::ref(m2Map),
                          A.second,
                          B.first,
                          C.first, C.second,
                          batchSize,
                          n,
                          sqrtThreadCount};
            v.push_back(move(t));
        }
    }

    for_each(v.begin(), v.end(), [](std::thread &t) {
        t.join();
    });
}

void testMatrixMatrixMult() {
    uint8_t iterations = 7;
    uint8_t threadsCount = 16;
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
        delete [] matrix1In;
        delete [] matrix2In;
        delete [] mOutParallelStriped;

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
        delete [] matrix1InLoopUnrolled;
        delete [] matrix2InLoopUnrolled;
        delete [] mOutParallelStripedLoopUnrolled;

        std::cout << "\nTp true horizontal:\n";
        auto mOutParallelStripedTrueHorizontal = new float [W[i]*W[i]];
        auto matrix1InTrueHorizontal = new float [W[i]*W[i]];
        auto matrix2InTrueHorizontal = new float [W[i]*W[i]];
        std::copy(matrix1, matrix1 + W[i]*W[i], matrix1InTrueHorizontal);
        std::copy(matrix2, matrix2 + W[i]*W[i], matrix2InTrueHorizontal);
        measure([&W, &matrix1InTrueHorizontal, &matrix2InTrueHorizontal, &mOutParallelStripedTrueHorizontal, threadsCount, i] {
            testMatrixMatrixMultParallelStripedTrueHorizontal(matrix1InTrueHorizontal, matrix2InTrueHorizontal, mOutParallelStripedTrueHorizontal, W[i], threadsCount);
        }, 1, "seconds", "nonverbose");
        verifyMatrices(mOutSerial, mOutParallelStripedTrueHorizontal, W[i]);
        delete [] matrix1InTrueHorizontal;
        delete [] matrix2InTrueHorizontal;
        delete [] mOutParallelStripedTrueHorizontal;

        std::cout << "\nTp true horizontal loop unrolled:\n";
        auto mOutParallelStripedTrueHorizontalLoopUnrolled = new float [W[i]*W[i]];
        auto matrix1InTrueHorizontalLoopUnrolled = new float [W[i]*W[i]];
        auto matrix2InTrueHorizontalLoopUnrolled = new float [W[i]*W[i]];
        std::copy(matrix1, matrix1 + W[i]*W[i], matrix1InTrueHorizontalLoopUnrolled);
        std::copy(matrix2, matrix2 + W[i]*W[i], matrix2InTrueHorizontalLoopUnrolled);
        measure([&W, &matrix1InTrueHorizontalLoopUnrolled, &matrix2InTrueHorizontalLoopUnrolled, &mOutParallelStripedTrueHorizontalLoopUnrolled, threadsCount, i] {
            testMatrixMatrixMultParallelStripedTrueHorizontalLoopUnrolled(matrix1InTrueHorizontalLoopUnrolled, matrix2InTrueHorizontalLoopUnrolled, mOutParallelStripedTrueHorizontalLoopUnrolled, W[i], threadsCount);
        }, 1, "seconds", "nonverbose");
        verifyMatrices(mOutSerial, mOutParallelStripedTrueHorizontalLoopUnrolled, W[i]);
        delete [] matrix1InTrueHorizontalLoopUnrolled;
        delete [] matrix2InTrueHorizontalLoopUnrolled;
        delete [] mOutParallelStripedTrueHorizontalLoopUnrolled;

        std::cout << "\nTp true horizontal loop unrolled std::vector<float>:\n";
        auto mOutParallelStripedTrueHorizontalLoopUnrolledVector = std::vector<float>(W[i]*W[i], 0);
        auto matrix1InTrueHorizontalLoopUnrolledVector = toVector(matrix1, W[i]*W[i]);
        auto matrix2InTrueHorizontalLoopUnrolledVector = toVector(matrix2, W[i]*W[i]);
        measure([&W, &matrix1InTrueHorizontalLoopUnrolledVector, &matrix2InTrueHorizontalLoopUnrolledVector, &mOutParallelStripedTrueHorizontalLoopUnrolledVector, threadsCount, i] {
            testMatrixMatrixMultParallelStripedTrueHorizontalLoopUnrolledVector(matrix1InTrueHorizontalLoopUnrolledVector, matrix2InTrueHorizontalLoopUnrolledVector, mOutParallelStripedTrueHorizontalLoopUnrolledVector, W[i], threadsCount);
        }, 1, "seconds", "nonverbose");
        verifyMatrices(mOutSerial, mOutParallelStripedTrueHorizontalLoopUnrolledVector, W[i]);

        std::cout << "\nTp Cannon's algorithm:\n";
        auto mOutParallelCannon = new float [W[i]*W[i]];
        auto matrix1InCannon = new float [W[i]*W[i]];
        auto matrix2InCannon = new float [W[i]*W[i]];
        std::copy(matrix1, matrix1 + W[i]*W[i], matrix1InCannon);
        std::copy(matrix2, matrix2 + W[i]*W[i], matrix2InCannon);
        measure([&W, &matrix1InCannon, &matrix2InCannon, &mOutParallelCannon, threadsCount, i] {
            testMatrixMatrixMultParallelCannon(matrix1InCannon, matrix2InCannon, mOutParallelCannon, W[i], threadsCount);
        }, 1, "seconds", "nonverbose");
        //verifyMatrices(mOutSerial, mOutParallelCannon, W[i]);
        delete [] matrix1InCannon;
        delete [] matrix2InCannon;
        delete [] mOutParallelCannon;

        std::cout << "\nTp Cannon's algorithm with condition variable:\n";
        auto mOutParallelCannonCondVar = new float [W[i]*W[i]];
        auto matrix1InCannonCondVar = new float [W[i]*W[i]];
        auto matrix2InCannonCondVar = new float [W[i]*W[i]];
        std::copy(matrix1, matrix1 + W[i]*W[i], matrix1InCannonCondVar);
        std::copy(matrix2, matrix2 + W[i]*W[i], matrix2InCannonCondVar);
        measure([&W, &matrix1InCannonCondVar, &matrix2InCannonCondVar, &mOutParallelCannonCondVar, threadsCount, i] {
            testMatrixMatrixMultParallelCannonCondVar(matrix1InCannonCondVar, matrix2InCannonCondVar, mOutParallelCannonCondVar, W[i], threadsCount);
        }, 1, "seconds", "nonverbose");
        //verifyMatrices(mOutParallelCannon, mOutParallelCannonCondVar, W[i]);
        delete [] matrix1InCannonCondVar;
        delete [] matrix2InCannonCondVar;
        delete [] mOutParallelCannonCondVar;

        delete [] matrix1;
        delete [] matrix2;
        delete [] mOutSerial;
    }
}
