//
// Created by Vitaliy on 8/11/20.
//
#include <vector>
#include <iostream>

void adjacentExample1() {
  std::vector<double> v = {100, 100.4, 100.7, 103, 104, 108.8, 140, 143, 145};

  if (auto it = std::adjacent_find(v.begin(), v.end(),
                                   [](const double p1, const double p2) { return p2 - p1 > 5; });
      it != v.end()) {
    std::cout << "First change in more than 5: "
              << std::distance(v.begin(), ++it) + 1
              << std::endl;
  }
}