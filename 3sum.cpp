//
// Created by Vitaliy on 2019-09-25.
//

#include "3sum.h"

std::vector<std::vector<int>> Sum3::threeSum(std::vector<int>& nums) {
  std::vector<std::vector<int>> result = {};
  if (nums.size() == 0)
    return result;

  sort(nums.begin(), nums.end());
  int N = nums.size();
  int l, r, target, sum;
  for (int i = 0; i<N; i++) {
    if (i > 0 && nums[i] == nums[i - 1]) {
      continue;
    }
    l = i+1;
    r = N-1;
    target = 0-nums[i];
    while (l<r){
      if (r < N - 1 && nums[r] == nums[r + 1]) {
        r--;
        continue;
      }
      sum = nums[l] + nums[r];
      if (sum == target) {
        result.push_back({nums[i], nums[l++], nums[r--]});
      } else if (sum < target) {
        l++;
      } else {
        r--;
      }
    }
  }

  return result;
}
