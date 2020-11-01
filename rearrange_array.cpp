//
// Created by Vitaliy on 2019-09-25.
// https://www.interviewbit.com/problems/rearrange-array/
//
#include <vector>

class MaxSubArray {
    void arrange(std::vector<int> &A) {
      int N = A.size();
      for(int i = 0; i < N; ++i) {
        A[i] = A[i] + (A[A[i]]%N) * N;
      }

      for(int i = 0; i < N; ++i) {
        A[i] = A[i] / N;
      }
    }
};
