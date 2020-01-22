//
// Created by Vitaliy on 2019-09-26.
//

#include "spiral-order-matrix-i.h"

void runTest(string &variationName, vector<vector<int>> &A, vector<int> &expected) {
  SpiralOrderMatrixI *solution = new SpiralOrderMatrixI();
  vector<int> result = solution->spiralOrder(A);
  if (result.size() != expected.size()) {
    cout << variationName + " FAIL size!" << "\nexpected:" << expected.size() << "\nresult:" << result.size() << endl;
  }
  for (int i = 0; i < expected.size(); ++i) {
    if (expected[i] != result[i])
      cout << "FAIL " + variationName + ": SpiralOrderMatrixI: \nresult[" << i << "] = '" << result[i] << "'\nexpected[" << i << "] = '" << expected[i] << "'" << endl;
  }
  cout << variationName + " SUCCESS!" << endl;
}

void spiralOrderMatrixITest() {
  string variationName;
  vector<vector<int>> A;
  vector<int> expected;

  variationName = "ex0";
  A = {};
  expected = {};
  runTest(variationName, A, expected);

  variationName = "ex1";
  A = {{1,2,3},{4,5,6},{7,8,9}};
  expected = {1,2,3,6,9,8,7,4,5};
  runTest(variationName, A, expected);

  variationName = "ex2";
  A = {{1,2,3}};
  expected = {1,2,3};
  runTest(variationName, A, expected);

  variationName = "ex3";
  A = {{1,2,3},{4,5,6}};
  expected = {1,2,3,6,5,4};
  runTest(variationName, A, expected);

  variationName = "ex4";
  A = {{1},{2},{3}};
  expected = {1,2,3};
  runTest(variationName, A, expected);
}
