//
// Created by Vitaliy on 2019-09-25.
//

#include "rotate_matrig.h"

void RotateMatrix::rotate(std::vector<std::vector<int> > &A) {
  // Do not write main() function.
  // Do not read input, instead use the arguments to the function.
  // Do not print the output, instead return values as specified
  // Still have a doubt. Checkout www.interviewbit.com/pages/sample_codes/ for more details

  if (A.size() <= 1) return;
  int N = A.size();
  if (A[0].size() <= 1) return;

  int temp1, temp2, temp3;
  for (int i = 0; i < N/2; i++) {
    for (int j = i; j < N-i-1; j++) {
      temp1 = A[j][N-1-i];
      A[j][N-1-i] = A[i][j];

      temp2 = A[N-1-i][N-1-j];
      A[N-1-i][N-1-j] = temp1;

      temp3 = A[N-1-j][i];
      A[N-1-j][i] = temp2;

      A[i][j] = temp3;
    }
  }

  return;
}

