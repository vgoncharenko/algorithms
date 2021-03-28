//
// Created by Vitaliy on 10/30/20.
//
#include <iostream>

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
    for (int i = 0; i < threadsCount; ++i) {
        std::thread t{rowMultTask, matrix, vOut, vIn, i*batchSize, (i+1)*batchSize, n};
        t.join();
    }
}

void verifyVectors(const float* expected, const float* actual, const uint64_t n) {
    for (int i = 0; i < n; ++i) {
        if (expected[i] != actual[i])
            std::cout << "error in index " << i << " expected=" << expected[i] << " actual=" << actual[i] << " diff=" << (expected[i]-actual[i]) << "\n";
    }
}

/**
 *
P=8
Iteration 0
W=1024
Ts:
Median of time taken by function: 3809 nanoseconds
Tp:
Median of time taken by function: 592109 nanoseconds
Iteration 1
W=4096
Ts:
Median of time taken by function: 9100 nanoseconds
Tp:
Median of time taken by function: 620558 nanoseconds
Iteration 2
W=16384
Ts:
Median of time taken by function: 34614 nanoseconds
Tp:
Median of time taken by function: 543215 nanoseconds
Iteration 3
W=65536
Ts:
Median of time taken by function: 136064 nanoseconds
Tp:
Median of time taken by function: 684850 nanoseconds
Iteration 4
W=262144
Ts:
Median of time taken by function: 582283 nanoseconds
Tp:
Median of time taken by function: 1889656 nanoseconds
Iteration 5
W=1048576
Ts:
Median of time taken by function: 2276375 nanoseconds
Tp:
Median of time taken by function: 5981433 nanoseconds
Iteration 6
W=4194304
Ts:
Median of time taken by function: 8850202 nanoseconds
Tp:
Median of time taken by function: 59266157 nanoseconds
Iteration 7
W=16777216
Ts:
Median of time taken by function: 36460935 nanoseconds
Tp:
Median of time taken by function: 329410951 nanoseconds
Iteration 8
W=67108864
Ts:
Median of time taken by function: 139286468 nanoseconds
Tp:
Median of time taken by function: 1545603236 nanoseconds
Iteration 9
W=268435456
Ts:
Median of time taken by function: 576185534 nanoseconds
Tp:
Median of time taken by function: 6181602612 nanoseconds
Iteration 10
W=1073741824
Ts:
Median of time taken by function: 2423606761 nanoseconds
Tp:
Median of time taken by function: 40568389126 nanoseconds



 P=16
 Iteration 0
W=1024
Ts:
Median of time taken by function: 3898 nanoseconds
Tp:
Median of time taken by function: 1152169 nanoseconds
Iteration 1
W=4096
Ts:
Median of time taken by function: 9424 nanoseconds
Tp:
Median of time taken by function: 741360 nanoseconds
Iteration 2
W=16384
Ts:
Median of time taken by function: 36242 nanoseconds
Tp:
Median of time taken by function: 865152 nanoseconds
Iteration 3
W=65536
Ts:
Median of time taken by function: 144659 nanoseconds
Tp:
Median of time taken by function: 1023548 nanoseconds
Iteration 4
W=262144
Ts:
Median of time taken by function: 576169 nanoseconds
Tp:
Median of time taken by function: 2214874 nanoseconds
Iteration 5
W=1048576
Ts:
Median of time taken by function: 2267029 nanoseconds
Tp:
Median of time taken by function: 7817892 nanoseconds
Iteration 6
W=4194304
Ts:
Median of time taken by function: 9270075 nanoseconds
Tp:
Median of time taken by function: 66025672 nanoseconds
Iteration 7
W=16777216
Ts:
Median of time taken by function: 51694823 nanoseconds
Tp:
Median of time taken by function: 309776650 nanoseconds
Iteration 8
W=67108864
Ts:
Median of time taken by function: 156049630 nanoseconds
Tp:
Median of time taken by function: 1312614132 nanoseconds
Iteration 9
W=268435456
Ts:
Median of time taken by function: 592997387 nanoseconds
Tp:
Median of time taken by function: 5450189165 nanoseconds
Iteration 10
W=1073741824
Ts:
Median of time taken by function: 2483316830 nanoseconds
Tp:
Median of time taken by function: 42919442545 nanoseconds


 P=32
Iteration 0
W=1024
Ts:
Median of time taken by function: 3876 nanoseconds
Tp:
Median of time taken by function: 2435597 nanoseconds
Iteration 1
W=4096
Ts:
Median of time taken by function: 9023 nanoseconds
Tp:
Median of time taken by function: 1282938 nanoseconds
Iteration 2
W=16384
Ts:
Median of time taken by function: 34537 nanoseconds
Tp:
Median of time taken by function: 1349627 nanoseconds
Iteration 3
W=65536
Ts:
Median of time taken by function: 132794 nanoseconds
Tp:
Median of time taken by function: 1596830 nanoseconds
Iteration 4
W=262144
Ts:
Median of time taken by function: 533095 nanoseconds
Tp:
Median of time taken by function: 2617405 nanoseconds
Iteration 5
W=1048576
Ts:
Median of time taken by function: 2178682 nanoseconds
Tp:
Median of time taken by function: 9911038 nanoseconds
Iteration 6
W=4194304
Ts:
Median of time taken by function: 8946225 nanoseconds
Tp:
Median of time taken by function: 57531172 nanoseconds
Iteration 7
W=16777216
Ts:
Median of time taken by function: 37730046 nanoseconds
Tp:
Median of time taken by function: 311747539 nanoseconds
Iteration 8
W=67108864
Ts:
Median of time taken by function: 146856660 nanoseconds
Tp:
Median of time taken by function: 1445248455 nanoseconds
Iteration 9
W=268435456
Ts:
Median of time taken by function: 633643096 nanoseconds
Tp:
Median of time taken by function: 6009597449 nanoseconds
Iteration 10
W=1073741824
Ts:
Median of time taken by function: 2547867355 nanoseconds
Tp:
Median of time taken by function: 42209859846 nanoseconds

 */
void testMatrixVectorMult() {
    uint8_t iterations = 11;
    uint8_t threadsCount = 8;
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
