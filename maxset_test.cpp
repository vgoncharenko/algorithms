//
// Created by Vitaliy on 2019-09-26.
//

#include "maxset.h"

void runTest(string variationName, vector<int> &A, vector<int> &expected)
{
  MaxSet *solution = new MaxSet();
  vector<int> result = solution->find(A);
  for (int i = 0; i < expected.size(); ++i) {
    if (expected[i] != result[i])
      cout << "FAIL " + variationName + ": MaxSet: \nresult[" << i << "] = '" << result[i] << "'\nexpected[" << i << "] = '" << expected[i] << "'" << endl;
  }
  cout << variationName + " SUCCESS!" << endl;
}

void maxSetTest() {
  string variationName;
  vector<int> A, expected;

  variationName = "ex0";
  A = {};
  expected = {};
  runTest(variationName, A, expected);

  variationName = "ex1";
  A = {0};
  expected = {0};
  runTest(variationName, A, expected);

  variationName = "ex2";
  A = {1,2,3};
  expected = {1,2,3};
  runTest(variationName, A, expected);

  variationName = "ex3";
  A = {1,2,3,0};
  expected = {1,2,3,0};
  runTest(variationName, A, expected);

  variationName = "ex4";
  A = {1,2,3,0,-1};
  expected = {1,2,3,0};
  runTest(variationName, A, expected);

  variationName = "ex5";
  A = {1,2,3,0,-1,0,0,0,0,0,0,0};
  expected = {1,2,3,0};
  runTest(variationName, A, expected);

  variationName = "ex6";
  A = {1,2,3,0,-1,0,0,0,0,0,0,0,1000};
  expected = {0,0,0,0,0,0,0,1000};
  runTest(variationName, A, expected);

  variationName = "ex7";
  A = {1,2,3,0,-1,-2,-2,-2,-2,1000};
  expected = {1000};
  runTest(variationName, A, expected);
}
