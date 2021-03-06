//
// Created by Vitaliy on 2019-09-26.
//

#include "median_of_two_sorted_arrays.cpp"

void runMedianOfTwoSortedArraysTest(std::string variationName, std::vector<int> ar1, std::vector<int> ar2, double expected)
{
  MedianOfTwoSortedArrays *solution = new MedianOfTwoSortedArrays();
//  double result = solution->findMedianSortedArrays(ar1, ar2);
  double result = solution->findMedianSortedArrays2(ar1, ar2);
  if (result != expected)
    std::cout << "FAIL " + variationName + ": MedianOfTwoSortedArrays: \nresult: '" << result << "'\nexpected: '" << expected << "'"<< std::endl;
  else
    std::cout << variationName + " SUCCESS!" << std::endl;
}

void medianOfTwoSortedArraysTest() {
  std::string variationName;
  std::vector<int> ar1, ar2;
  double expected;

  variationName = "ex0";
  ar1 = {2,8,100};
  ar2 = {1,100,101};
  expected = 54;
  runMedianOfTwoSortedArraysTest(variationName, ar1, ar2, expected);

  variationName = "ex1";
  ar1 = {2,8,100};
  ar2 = {1,100,101,102};
  expected = 100;
  runMedianOfTwoSortedArraysTest(variationName, ar1, ar2, expected);

  variationName = "ex2";
  ar1 = {1,2};
  ar2 = {3,4};
  expected = 2.5;
  runMedianOfTwoSortedArraysTest(variationName, ar1, ar2, expected);

  variationName = "ex3";
  ar1 = {2};
  ar2 = {1};
  expected = 1.5;
  runMedianOfTwoSortedArraysTest(variationName, ar1, ar2, expected);

  variationName = "ex4";
  ar1 = {1,2};
  ar2 = {1};
  expected = 1;
  runMedianOfTwoSortedArraysTest(variationName, ar1, ar2, expected);

  variationName = "ex5";
  ar1 = {1};
  ar2 = {1,2};
  expected = 1;
  runMedianOfTwoSortedArraysTest(variationName, ar1, ar2, expected);

  variationName = "ex6";
  ar1 = {1,1,1,1,1,1,1};
  ar2 = {1,1};
  expected = 1;
  runMedianOfTwoSortedArraysTest(variationName, ar1, ar2, expected);
}
