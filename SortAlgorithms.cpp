//
// Created by Vitaliy on 10/30/20.
//
#include <iostream>
#include <exception>
#include <complex.h>

//auto getVector(const uint64_t n) {
//    std::vector<int> vector = {10,20,5,9,3,8,12,14,90,0,60,40,23,35,95,18};
//    return vector;
//}

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
        const int chunk = n/pow(2, i);
        const int doubleChunk = chunk * 2;
        for (int j = 0; j < n/doubleChunk; ++j) {
            bitonicSplit(begin + j*doubleChunk, begin + j*doubleChunk + chunk, cmp);
        }
    }
}

template<typename I>
void bitonicSort(I begin, const uint64_t n) {
    for (int i = 0; i < log2(n/2); ++i) {
        const int chunk = pow(2, i);
        const int doubleChunk = chunk * 2;
        for (int j = 0; j < n/doubleChunk; ++j) {
            if (j%2) bitonicMerge(begin + j*doubleChunk, doubleChunk, [](auto const it1, auto const it2) {return *it1 < *it2;});
            else bitonicMerge(begin + j*doubleChunk, doubleChunk, [](auto const it1, auto const it2) {return *it1 > *it2;});
        }
    }
}

template<typename I, typename cmpFunction>
void bitoicSortSerial(I vInBegin, const uint64_t n, cmpFunction cmp) {
    bitonicSort(vInBegin, n);
    bitonicMerge(vInBegin, n, cmp);
}

template<typename I>
void bitonicSortParallel(I begin, const uint64_t n, const uint8_t threadCount) {
//    std::cout << "initial:\n";
//    for (int i = 0; i < n; ++i) {
//        std::cout << *(begin + i) << ',';
//    }
    std::function<bool(const float*, const float*)> asc = [](auto const it1, auto const it2) {return *it1 > *it2;};
    std::function<bool(const float*, const float*)> desc = [](auto const it1, auto const it2) {return *it1 < *it2;};

    // Sort blocks internally
    std::vector<std::thread> sortStep;
    for (int i = 0; i < threadCount; ++i) {
        std::thread t{bitoicSortSerial<float*, std::function<bool(const float*, const float*)>>,
                      begin + n/threadCount * i,
                      n/threadCount,
                      (i%2) ? desc : asc
        };
        sortStep.push_back(move(t));
    }
    for_each(sortStep.begin(), sortStep.end(), [](std::thread &t) {
        t.join();
    });

    //Perform Only Merges
    for (int k = 1; k <= log2(threadCount); ++k) {
        const int threads = threadCount / pow(2, k);
        const uint64_t blockSize = n / threads;
        std::vector<std::thread> mergeStep;
        for (int i = 0; i < threads; ++i) {
            std::thread t{bitonicMerge<float*, std::function<bool(const float*, const float*)>>,
                          begin + blockSize * i,
                          blockSize,
                          (i%2) ? desc : asc
            };
            mergeStep.push_back(move(t));
        }
        for_each(mergeStep.begin(), mergeStep.end(), [](std::thread &t) {
            t.join();
        });
//        std::cout << "\n\niteration " << k << ":\n";
//        for (int i = 0; i < n; ++i) {
//            std::cout << *(begin + i) << ',';
//        }
    }
}

template<typename I>
void testBitonicSortSerial(I vInBegin, const uint64_t n) {
    bitoicSortSerial(vInBegin, n, [](auto const it1, auto const it2) {return *it1 > *it2;});
}

template<typename I>
void testBitonicSortParallel(I vInBegin, const uint64_t n, const uint8_t threadCount) {
    bitonicSortParallel(vInBegin, n, threadCount);
}

void sanityCheck()
{
//    std::vector<int> input = {3,5,8,9,10,12,14,20,95,90,60,40,35,23,18,0};
    std::vector<int> input = {10,20,5,9,3,8,12,14,90,0,60,40,23,35,95,18};
    std::vector<int> expected(input.size());
    std::copy(input.begin(), input.end(), expected.begin());
    std::sort(expected.begin(), expected.end());
    testBitonicSortSerial(std::begin(input), input.size());
    verifyVectors(expected, input, input.size());
}

void testVectorSort() {
//    sanityCheck();
    uint8_t iterations = 20;
    uint8_t threadsCount = 16;
    auto W = new int[iterations];
    W[0] = 32;
    uint8_t q = 2;
    for (int i = 1; i < iterations; ++i) {
        W[i] = W[i-1] * q;
    }

    for (int i = 0; i < iterations; ++i) {
//        float vIn[] = {10,20,5,9,3,8,12,14,90,0,60,40,23,35,95,18,101,103,105,106,108,1010,111,112,113,114,115,116,117,118,119,223};
        auto vIn = getVector(W[i]);
        auto expected = new float [W[i]];
        std::copy(vIn, vIn + W[i], expected);
        std::sort(expected, expected + W[i]);

//        std::cout << "\nIteration " << i << "\n";
//        std::cout << "W=" << W[i] * W[i] << "\n";
//        std::cout << "Ts:\n";
//        auto vOutSerial = new float [W[i]];
//        std::copy(vIn, vIn + W[i], vOutSerial);
//        measure([&W, &vOutSerial, i] {
//            testBitonicSortSerial(vOutSerial, W[i]);
//        }, 1, "seconds", "nonverbose");
//        verifyVectors(expected, vOutSerial, W[i]);
//        delete [] vOutSerial;

        //std::cout << "Tp:\n";
        auto vOutParallel = new float [W[i]];
        std::copy(vIn, vIn + W[i], vOutParallel);
        measure([&W, &vOutParallel, threadsCount, i] {
            testBitonicSortParallel(vOutParallel, W[i], threadsCount);
        }, 1, "seconds", "nonverbose");
        verifyVectors(expected, vOutParallel, W[i]);
        delete [] vOutParallel;

        delete [] vIn;
    }
}
