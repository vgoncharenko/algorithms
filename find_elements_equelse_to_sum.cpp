//
// Created by Vitaliy on 2019-09-23.
//

#include "find_elements_equelse_to_sum.h"

std::vector<int> SolutionOfSum::twoSum(std::vector<int> &nums, int target) {
    std::map<int, int> myMap;
  int complement;

  for (int i = 0; i < nums.size(); i++) {
    complement = target - nums[i];
    auto index = myMap.find(complement);
    if (index != myMap.end()) {
      return std::vector<int>{index->second, i};
    }
    myMap.insert({nums[i], i});
  }

  return std::vector<int>{0};
}
