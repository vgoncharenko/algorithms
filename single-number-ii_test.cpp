//
// Created by Vitaliy on 2019-09-26.
//

#include "single-number-ii.h"

void runSingleNumberIITest(string &variationName, vector<int> &nums, int expected) {
  SingleNumberII *solution = new SingleNumberII();
  int result = solution->singleNumber(nums);
  if (result != expected)
    cout << "FAIL " + variationName + ": SingleNumberII: \nresult: '" << result << "'\nexpected: '" << expected << "'"<< endl;
  else
    cout << variationName + " SUCCESS!" << endl;
}

void singleNumberIITest() {
  string variationName;
  vector<int> nums;
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
