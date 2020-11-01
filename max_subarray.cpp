//
// Created by Vitaliy on 2019-09-25.
// https://www.interviewbit.com/problems/max-sum-contiguous-subarray/
//
#include <vector>

class MaxSubArray {
    int maxSubArray(const std::vector<int> &A) {
      int n = A.size();
      int curSum = 0, maxSum = -1000000000;
      for (int i = 0; i < n; i++) {
        curSum += A[i];
        maxSum = std::max(maxSum, curSum);
        if (curSum < 0)
          curSum = 0;
      }
      return maxSum;
    }
};
