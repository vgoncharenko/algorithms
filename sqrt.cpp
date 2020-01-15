//
// Created by Vitaliy on 2019-09-25.
//

#include "sqrt.h"

int SQRT::sqrt(int x) {
//  return floor(std::sqrt(x));
  if (x == 0) {
    return 0;
  }
  if (x <= 3) return 1;

  int start = 1,
      end = x,
      result,
      mid;

  while (start <= end) {
    mid = (start + end) / 2;
    if (mid <= x/mid) {
      start = mid + 1;
      result = mid;
    } else {
      end = mid - 1;
    }
  }

  return result;
}
