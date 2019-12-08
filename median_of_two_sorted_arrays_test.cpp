//
// Created by Vitaliy on 2019-09-26.
//

#include "median_of_two_sorted_arrays.h"

void runTest(string variationName, vector<int> ar1, vector<int> ar2, double expected)
{
  MedianOfTwoSortedArrays *solution = new MedianOfTwoSortedArrays();
  double result = solution->findMedianSortedArrays(ar1, ar2);
  if (result != expected)
    cout << "FAIL " + variationName + ": MedianOfTwoSortedArrays: \nresult: '" << result << "'\nexpected: '" << expected << "'"<< endl;
  else
    cout << variationName + " SUCCESS!" << endl;
}

void medianOfTwoSortedArraysTest() {
  string variationName;
  vector<int> ar1, ar2;
  double expected;

  variationName = "ex0";
  ar1 = {2,8,100};
  ar2 = {1,100,101};
  expected = 54;
  runTest(variationName, ar1, ar2, expected);

  variationName = "ex1";
  ar1 = {2,8,100};
  ar2 = {1,100,101,102};
  expected = 100;
  runTest(variationName, ar1, ar2, expected);

  variationName = "ex2";
  ar1 = {1,2};
  ar2 = {3,4};
  expected = 2.5;
  runTest(variationName, ar1, ar2, expected);

  variationName = "ex3";
  ar1 = {2};
  ar2 = {1};
  expected = 1.5;
  runTest(variationName, ar1, ar2, expected);

  variationName = "ex4";
  ar1 = {1,2};
  ar2 = {1};
  expected = 1;
  runTest(variationName, ar1, ar2, expected);

  variationName = "ex5";
  ar1 = {1};
  ar2 = {1,2};
  expected = 1;
  runTest(variationName, ar1, ar2, expected);

  variationName = "ex6";
  ar1 = {1,1,1,1,1,1,1};
  ar2 = {1,1};
  expected = 1;
  runTest(variationName, ar1, ar2, expected);
}
