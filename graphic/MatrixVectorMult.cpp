//
// Created by Vitaliy on 10/30/20.
//
#include <iostream>
#include <mpi.h>

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

// narrow data passing to threads
// loop unrolling (ptr over int indexes)
// clang optimizations
// MPI implementation
void rowMultTask(const float* m,
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

void testMatrixVectorMultParallelStriped(float* matrix,
                                         const float* vIn,
                                         float* vOut,
                                         const uint64_t n,
                                         const uint8_t threadsCount) {
    uint64_t batchSize = n / threadsCount;
    std::vector<std::thread> v;
    for (int i = 0; i < threadsCount; ++i) {
        std::thread t{rowMultTask, &matrix[i*batchSize], vOut, vIn, i*batchSize, (i+1)*batchSize, n};
        v.push_back(move(t));
    }
    for_each(v.begin(), v.end(), [](std::thread &t){
        t.join();
    });
}

// Data distribution among the processes
void DataDistribution(const float* pMatrix,
                      float* pProcRows,
                      float* pVector,
                      const uint64_t Size,
                      int RowNum,
                      int ProcNum,
                      int ProcRank) {
    int *pSendNum; // the number of elements sent to the process
    int *pSendInd; // the index of the first data element sent to the process
    int RestRows=Size; // Number of rows, that haven’t been distributed yet

    MPI_Bcast(pVector, Size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
// Alloc memory for temporary objects
    pSendInd = new int [ProcNum];
    pSendNum = new int [ProcNum];
// Define the disposition of the matrix rows for current process
    RowNum = (Size/ProcNum);
    pSendNum[0] = RowNum*Size;
    pSendInd[0] = 0;
    for (int i=1; i<ProcNum; i++) {
        RestRows -= RowNum;
        RowNum = RestRows/(ProcNum-i);
        pSendNum[i] = RowNum*Size;
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
    int *argc;
    char ***argv;
    int ProcRank = 1;
    float* pProcRows;
    float* pProcResult;
    int RowNum;
    MPI_Init(argc, argv);
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

void testMatrixVectorMult() {
    uint8_t iterations = 5;
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

        //verifyVectors(vOutSerial, vOutParallelStriped, W[i]);

        delete [] matrix;
        delete [] vIn;
        delete [] vOutSerial;
        delete [] matrixIn;
        delete [] vOutParallelStriped;
    }
}
