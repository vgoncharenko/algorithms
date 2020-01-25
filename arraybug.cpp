//
// Created by Vitaliy on 2019-09-25.
//

#include "arraybug.h"

vector<int> ArrayBug::rotateArray(vector<int> & A, int B) {
  vector<int> ret;
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
