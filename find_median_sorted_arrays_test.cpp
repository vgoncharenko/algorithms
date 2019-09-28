//
// Created by Vitaliy on 2019-09-26.
//

#include "find_median_sorted_arrays.h"


void testFindMedianSortedArrays() {
  vector<int> v1 = {1, 3};
  vector<int> v2 = {2};
  double expected = 2;
  auto *solution = new FindMedianSortedArrays();
  double result;
//  result = solution->compute(v1, v2);

//  if (expected != result)
//    cout << "FAIL: testfindMedianSortedArrays: \nexpected: " << expected << "\nactual: " << result << endl;

  v1 = {1, 2};
  v2 = {3, 4};
  expected = 2.5;
//  result = solution->compute(v1, v2);

//  if (expected != result)
//    cout << "FAIL: testfindMedianSortedArrays: \nexpected: " << expected << "\nactual: " << result << endl;

  v1 = {44, 45, 56, 63, 64, 65, 66, 96, 783};
  v2 = {16, 30, 33, 35, 37};
  expected = 50.5;
  result = solution->compute(v1, v2);

  if (expected != result)
    cout << "FAIL: testfindMedianSortedArrays: \nexpected: " << expected << "\nactual: " << result << endl;
}