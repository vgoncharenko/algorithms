//
// Created by Vitaliy on 2019-09-25.
//

#include "single-number-ii.h"

int SingleNumberII::singleNumber(vector<int> &nums) {
  int ones = 0,
      twos = 0;
  for (int i = 0; i < nums.size(); ++i) {
    ones = (ones^nums[i]) & ~twos;
    twos = (twos^nums[i]) & ~ones;
  }

  return ones;
}
