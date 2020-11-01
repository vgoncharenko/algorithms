//
// Created by Vitaliy on 2019-09-26.
//

#include "single-number-ii.cpp"

void runSingleNumberIITest(std::string &variationName, std::vector<int> &nums, int expected) {
  SingleNumberII *solution = new SingleNumberII();
  int result = solution->singleNumber(nums);
  if (result != expected)
    std::cout << "FAIL " + variationName + ": SingleNumberII: \nresult: '" << result << "'\nexpected: '" << expected << "'"<< std::endl;
  else
    std::cout << variationName + " SUCCESS!" << std::endl;
}

void singleNumberIITest() {
  std::string variationName;
  std::vector<int> nums;
  int expected;

  variationName = "ex0";
  nums = {3,3,3,2};
  expected = 2;
  runSingleNumberIITest(variationName, nums, expected);

  variationName = "ex1";
  nums = {1,1,1,2,3,3,3,5,5,5,7,7,7};
  expected = 2;
  runSingleNumberIITest(variationName, nums, expected);

  variationName = "ex2";
  nums = {1,1,1,2,2,2,3,3,3,5,5,5,7,7,7,9};
  expected = 9;
  runSingleNumberIITest(variationName, nums, expected);
}
