//
// Created by Vitaliy on 2019-09-23.
//

#include "find_elements_equelse_to_sum.h"

vector<int> SolutionOfSum::twoSum(vector<int> &nums, int target) {
  map<int, int> myMap;
  int complement;
  map<int, int, __1::less<int>, __1::allocator<__1::pair<const int, int>>>::iterator index;

  for (int i = 0; i < nums.size(); i++) {
    complement = target - nums[i];
    index = myMap.find(complement);
    if (index != myMap.end()) {
      return vector<int>{index->second, i};
    }
    myMap.insert({nums[i], i});
  }

  return vector<int>{0};
}

void testSolutionOfSum ()
{
  std::vector<int> vecOfNums = { 33, 45, 54, 1, 3, 7, 8, 22, 43, 19 };
  int target = 9;
  auto * solution = new SolutionOfSum();
  std::vector<int> result = solution->twoSum(vecOfNums, target);
  for (int i : result)
    std::cout << ' ' << i;
  std::cout << '\n';
}
