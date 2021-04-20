//
// Created by Vitaliy on 10/30/20.
//
#include <iostream>
#include <exception>

//auto getVector(const uint64_t n) {
//    auto vector = new float [n];
//
//    for (int i = 0; i < n; ++i) {
//        vector[i] = random() / MAXFLOAT;
//    }
//
//    return vector;
//}

template<typename T>
void verifyVectors(const T& expected, const T& actual, const uint64_t n) {
    for (int i = 0; i < n; ++i) {
        if (expected[i] != actual[i])
            std::cout << "error in index " << i << " expected=" << expected[i] << " actual=" << actual[i] << " diff=" << (expected[i]-actual[i]) << "\n";
    }
}

template<typename I, typename cmpFunction>
void bitonicCompareExchange(I &it1, I &it2, cmpFunction cmp) {
    if (cmp(it1, it2)) {
        auto tmp = *it2;
        *it2 = *it1;
        *it1 = tmp;
    }
}

template<typename I, typename cmpFunction>
void bitonicSplit(I it1, I it2, cmpFunction cmp) {
    I end = it2;
    while (it1 != end) {
        bitonicCompareExchange(it1, it2, cmp);
        ++it1; ++it2;
    }
}

template<typename I, typename cmpFunction>
void bitonicMerge(I begin, const uint64_t n, cmpFunction cmp) {
    for (int i = 1; i <= log2(n); ++i) {
        const auto chunk = n/pow(2, i);
        const auto doubleChunk = chunk * 2;
        for (int j = 0; j < n/doubleChunk; ++j) {
            bitonicSplit(begin + j*doubleChunk, begin + j*doubleChunk + chunk, cmp);
        }
    }
}

template<typename I>
void bitonicSort(I begin, const uint64_t n) {
    for (int i = 0; i < log2(n/2); ++i) {
        const auto chunk = pow(2, i);
        const auto doubleChunk = chunk * 2;
        for (int j = 0; j < n/doubleChunk; ++j) {
            if (j%2) bitonicMerge(begin + j*doubleChunk, doubleChunk, [](auto const it1, auto const it2) {return *it1 < *it2;});
            else bitonicMerge(begin + j*doubleChunk, doubleChunk, [](auto const it1, auto const it2) {return *it1 > *it2;});
        }
    }
}

template<typename I>
void testBitonicSortSerial(I vInBegin, I vOutBegin, const uint64_t n) {
    bitonicSort(vInBegin, n);
    bitonicMerge(vInBegin, n, [](auto const it1, auto const it2) {return *it1 > *it2;});
    std::copy(vInBegin, vInBegin+n, vOutBegin);
}

void sanityCheck()
{
//    std::vector<int> input = {3,5,8,9,10,12,14,20,95,90,60,40,35,23,18,0};
    std::vector<int> input = {10,20,5,9,3,8,12,14,90,0,60,40,23,35,95,18};
    std::vector<int> expected(input.size());
    std::copy(input.begin(), input.end(), expected.begin());
    std::sort(expected.begin(), expected.end());
    std::vector<int> output(input.size());
    testBitonicSortSerial(std::begin(input), std::begin(output), input.size());
    verifyVectors(expected, output, input.size());
}

void testVectorSort() {
    sanityCheck();
//    uint8_t iterations = 11;
//    uint8_t threadsCount = 16;
//    auto W = new int[iterations];
//    W[0] = 32;
//    uint8_t q = 2;
//    for (int i = 1; i < iterations; ++i) {
//        W[i] = W[i-1] * q;
//    }
//
//    for (int i = 0; i < iterations; ++i) {
//        auto vIn = getVector(W[i]);
//        auto vOutSerial = new float [W[i]];
//
//        std::cout << "\nIteration " << i << "\n";
//        std::cout << "W=" << W[i] * W[i] << "\n";
//        std::cout << "Ts:\n";
//        measure([&W, &vIn, &vOutSerial, i] {
//            testBitonicSortSerial(vIn, vOutSerial, W[i]);
//        }, 1, "seconds", "nonverbose");
//
////        std::cout << "\nTp:\n";
////        auto vOutParallelStriped = new float [W[i]];
////        auto matrixIn = new float [W[i]*W[i]];
////        std::copy(matrix, matrix + W[i]*W[i], matrixIn);
////        measure([&W, &matrixIn, &vIn, &vOutParallelStriped, threadsCount, i] {
////            testMatrixVectorMultParallelStriped(matrixIn, vIn, vOutParallelStriped, W[i], threadsCount);
////        }, 1, "seconds", "nonverbose");
////        verifyVectors(vOutSerial, vOutParallelStriped, W[i]);
//
//        delete [] vIn;
//        delete [] vOutSerial;
//    }
}
