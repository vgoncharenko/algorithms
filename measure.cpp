//
// Created by Vitaliy on 9/21/20.
//
#include <chrono>
#include <iostream>
#include <vector>

template <typename Callable>
void measure(Callable f, int iterations = 10) {
  std::vector<long> results(iterations);
  for (int i = 0; i < iterations; i++) {
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    results[i] = duration.count();
  }

  std::sort(results.begin(), results.end());
  std::cout << "Median of time taken by function: "
            << results[iterations/2] << " nanoseconds" << std::endl;
}