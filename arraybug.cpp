//
// Created by Vitaliy on 2019-09-25.
//

#include "arraybug.h"

std::vector<int> ArrayBug::rotateArray(std::vector<int> & A, int B) {
  std::vector<int> ret;
  if (A.size() == 0 || B == 0)
    return A;
  B = B % A.size();

  for (int i = 0; i < A.size() - B; i++) {
    ret.push_back(A[i + B]);
  }

  for (int i = 0; i < B; i++) {
    ret.push_back(A[i]);
  }

  return ret;
}
