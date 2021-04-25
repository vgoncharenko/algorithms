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

// O(1)
template<typename I, typename cmpFunction>
void bitonicCompareExchange(I &it1, I &it2, cmpFunction cmp) {
    if (cmp(it1, it2)) {
        auto tmp = *it2;
        *it2 = *it1;
        *it1 = tmp;
    }
}

// O(n)
template<typename I, typename cmpFunction>
void bitonicSplit(I it1, I it2, cmpFunction cmp) {
    I end = it2;
    while (it1 != end) {
        bitonicCompareExchange(it1, it2, cmp);
        ++it1; ++it2;
    }
}

// O(log2(n)*O(n))
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

// O(log2(n/2)*O(n*log2(n)))
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
class BlockBarrier {
private:
    int count = 0;
    uint64_t infLimit;
public:
    std::condition_variable condition;
    mutable std::mutex m;
    bool syncAllowed = false;

    explicit BlockBarrier (const uint64_t _infLimit) : infLimit(_infLimit) {};

    BlockBarrier& operator++ () {
        {
            std::scoped_lock lk(m);
            ++count;
        }

        if (infLimit >= count) {
            {
                std::scoped_lock lk(m);
                syncAllowed = true;
            }
            condition.notify_all();
        }

        return *this;
    }

    void reset() {
        std::scoped_lock lk(m);
        count = 0;
        syncAllowed = false;
    }
};

template<typename T>
void compareSplit(T* begin, const uint64_t n, bool directionFlag,
                  std::shared_ptr<BlockBarrier> barrier) {
    T* end = begin + n;
    auto newContainer = new T[n];
    T* it = newContainer;
    T* curBegin = begin;
    if (directionFlag) {
        T* endLover = curBegin - 1;
        T* endCur = end - 1;
        while (curBegin <= endCur && endLover > curBegin - 1 - n) {
            if (*endCur > *endLover) {
                *it = *endCur;
                --endCur;
            } else {
                *it = *endLover;
                --endLover;
            }
            ++it;
        }
        std::reverse(newContainer, newContainer + n);
    } else {
        T* beginUpper = end;
        while (curBegin < end && beginUpper < end + n) {
            if (*curBegin > *beginUpper) {
                *it = *beginUpper;
                ++beginUpper;
            } else {
                *it = *curBegin;
                ++curBegin;
            }
            ++it;
        }
    }
    //sync with other part, then substitute
    // add one pass to barrier
    barrier->operator++();
    // wait for opposite side to finish compare
    std::unique_lock<std::mutex> blockM1Lock(barrier->m);
    barrier->condition.wait(blockM1Lock, [&barrier] { return barrier->syncAllowed; });
    // perform split
    std::copy(newContainer, newContainer + n, begin);
}

// O(log2(n/2)*O(n*log2(n))) + O(log2(n)*O(n)) ~ O(n*(log2(n))^2)
template<typename I, typename cmpFunction>
void bitoicSortSerial(I vInBegin, const uint64_t n, cmpFunction cmp) {
    bitonicSort(vInBegin, n);
    bitonicMerge(vInBegin, n, cmp);
}

// O(O(log2(n/p/2)*O(n/p*log2(n/p))) + O(log2(n/p)*O(n/p))) + O(log2(p)-1) * O(log2(n) * O(n))
template<typename I>
void bitonicSortParallel(I begin, const uint64_t n, const uint8_t threadCount) {
//    std::cout << "initial:\n";
//    for (int i = 0; i < n; ++i) {
//        std::cout << *(begin + i) << ',';
//    }
    std::function<bool(const float*, const float*)> asc = [](auto const it1, auto const it2) {return *it1 > *it2;};
    std::function<bool(const float*, const float*)> desc = [](auto const it1, auto const it2) {return *it1 < *it2;};

    // Sort blocks internally
    // O(O(log2(n/p/2)*O(n/p*log2(n/p))) + O(log2(n/p)*O(n/p)))
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
    // O(log2(n/p/2) * O(n/p/2)) + O(log2(n/p/4) * O(n/p/4)) + ... + O(log2(n) * O(n))
    // with small enough p:
    // O(log2(p)-1) * O(log2(n) * O(n))
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

// O(O(log2(n/p/2)*O(n/p*log2(n/p))) + O(log2(n/p)*O(n/p))) + O(log2(p)-1) * O(log2(n) * O(n))
template<typename I>
void testBitonicSortCompareSplitParallel(I begin, const uint64_t n, const uint8_t threadCount) {
    std::cout << "initial:\n";
    for (int i = 0; i < n; ++i) {
        std::cout << *(begin + i) << ',';
    }
    std::function<bool(const float*, const float*)> asc = [](auto const it1, auto const it2) {return *it1 > *it2;};
    std::function<bool(const float*, const float*)> desc = [](auto const it1, auto const it2) {return *it1 < *it2;};

    // Sort blocks internally
    // O(O(log2(n/p/2)*O(n/p*log2(n/p))) + O(log2(n/p)*O(n/p)))
    std::vector<std::thread> sortStep;
    for (int i = 0; i < threadCount; ++i) {
        std::thread t{bitoicSortSerial<float*, std::function<bool(const float*, const float*)>>,
                      begin + n/threadCount * i,
                      n/threadCount,
                      asc
        };
        sortStep.push_back(move(t));
    }
    for_each(sortStep.begin(), sortStep.end(), [](std::thread &t) {
        t.join();
    });
    std::cout << "\n\nAfter first local sort:\n";
    for (int i = 0; i < n; ++i) {
        std::cout << *(begin + i) << ',';
    }

    //Perform Only Compare-Splits
    for (int k = 0; k < log2(threadCount); ++k) {
        const uint64_t threads = threadCount / pow(2, k);
        const uint64_t blockSize = n / threads;
        std::shared_ptr<BlockBarrier> barrier(new BlockBarrier(threads));
        std::vector<std::thread> mergeStep;
        for (int i = 0; i < threads; i+=2) {
            std::thread lower{compareSplit<float>,
                          begin + blockSize * i,
                          blockSize,
                          false,
                          std::ref(barrier)
            };
            std::thread upper{compareSplit<float>,
                          begin + blockSize * i + blockSize,
                          blockSize,
                          true,
                          std::ref(barrier)
            };
            mergeStep.push_back(move(lower));
            mergeStep.push_back(move(upper));
        }
        for_each(mergeStep.begin(), mergeStep.end(), [](std::thread &t) {
            t.join();
        });
        std::cout << "\n\niteration " << k << ":\n";
        for (int i = 0; i < n; ++i) {
            std::cout << *(begin + i) << ',';
        }
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
    uint8_t iterations = 1;
    uint8_t threadsCount = 16;
    auto W = new int[iterations];
    W[0] = 32;
    uint8_t q = 2;
    for (int i = 1; i < iterations; ++i) {
        W[i] = W[i-1] * q;
    }

    for (int i = 0; i < iterations; ++i) {
        float vIn[] = {10,20,5,9,3,8,12,14,90,0,60,40,23,35,95,18,101,111,115,116,103,105,113,114,106,223,108,1010,117,112,118,119};
//        auto vIn = getVector(W[i]);
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
//        auto vOutBitonicParallel = new float [W[i]];
//        std::copy(vIn, vIn + W[i], vOutBitonicParallel);
//        measure([&W, &vOutBitonicParallel, threadsCount, i] {
//            testBitonicSortParallel(vOutBitonicParallel, W[i], threadsCount);
//        }, 1, "seconds", "nonverbose");
//        verifyVectors(expected, vOutBitonicParallel, W[i]);
//        delete [] vOutBitonicParallel;

        auto vOutBitonicCompareSplitParallel = new float [W[i]];
        std::copy(vIn, vIn + W[i], vOutBitonicCompareSplitParallel);
        measure([&W, &vOutBitonicCompareSplitParallel, threadsCount, i] {
            testBitonicSortCompareSplitParallel(vOutBitonicCompareSplitParallel, W[i], threadsCount);
        }, 1, "seconds", "nonverbose");
        verifyVectors(expected, vOutBitonicCompareSplitParallel, W[i]);
        delete [] vOutBitonicCompareSplitParallel;

//        delete [] vIn;
    }
}
