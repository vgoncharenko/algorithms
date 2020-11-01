//
// Created by Vitaliy on 2019-09-25.
//

#include "spiral-order-matrix-i.h"

std::vector<int> SpiralOrderMatrixI::spiralOrder(const std::vector<std::vector<int>> &A) {
  int N = A.size();
  if (N == 0) return {};
  int M = A[0].size();

  std::vector<int> result;

  int TOP = 0,
          BOTTOM = N - 1,
          LEFT = 0,
          RIGHT = M - 1,
          dir = 0;

  int i,j;

  while (TOP <= BOTTOM && LEFT <= RIGHT) {
    switch (dir) {
      case 0: {
        // to right:
        i = TOP;
        for (j = LEFT; j <= RIGHT; ++j) {
          result.push_back(A[i][j]);
        }
        TOP++;
        dir = 1;
        break;
      }
      case 1: {
        //to down:
        j = RIGHT;
        for (i = TOP; i <= BOTTOM; ++i) {
          result.push_back(A[i][j]);
        }
        RIGHT--;
        dir = 2;
        break;
      }
      case 2: {
        //to left:
        i = BOTTOM;
        for (j = RIGHT; j >= LEFT; --j) {
          result.push_back(A[i][j]);
        }
        BOTTOM--;
        dir = 3;
        break;
      }
      case 3: {
        //to up:
        j = LEFT;
        for (i = BOTTOM; i >= TOP; --i) {
          result.push_back(A[i][j]);
        }
        LEFT++;
        dir = 0;
        break;
      }
    }
  }

  return result;
}
