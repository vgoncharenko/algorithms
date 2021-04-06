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
