//
// Created by Vitaliy on 2019-09-25.
//

#include "maxset.h"

std::vector<int> MaxSet::find(std::vector<int> &A) {
  std::vector<int> result = {},
          tempA = {};
  uint64_t sum = 0,
          maxSum = 0;

  for (int i; i < A.size(); i++) {
    if (A[i] >= 0) {
      tempA.push_back(A[i]);
      sum += A[i];
    }
    if (A[i] < 0 || i == A.size() - 1) {
      if (sum > maxSum // general case
          || (sum == maxSum && tempA.size() > result.size()) // 1 extra case
      ) {
        maxSum = sum;
        result = tempA;
      }
      sum = 0;
      tempA = {};
    }
  }

  return result;
}
