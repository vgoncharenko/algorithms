//
// Created by Vitaliy on 2019-09-25.
//

#include "arraybug.h"

vector<int> ArrayBug::rotateArray(vector<int> & A, int B) {
  vector<int> ret;
  if (B == A.size() || A.size() == 0) return A;
  if (B > A.size()) B = B % A.size();
  if (B == 0) return A;

  for (int i = 0; i < A.size() - B; i++) {
    ret.push_back(A[i + B]);
  }

  for (int i = 0; i < B; i++) {
    ret.push_back(A[i]);
  }

  return ret;
}
