//
// Created by Vitaliy on 2019-09-26.
//

#include "arraybug.h"

void runTest(string variationName, vector<int> &A, int B, vector<int> &expected)
{
  ArrayBug *solution = new ArrayBug();
  vector<int> result = solution->rotateArray(A, B);
  for (int i = 0; i < expected.size(); ++i) {
    if (expected[i] != result[i])
      cout << "FAIL " + variationName + ": MaxSet: \nresult[" << i << "] = '" << result[i] << "'\nexpected[" << i << "] = '" << expected[i] << "'" << endl;
  }
  cout << variationName + " SUCCESS!" << endl;
}

void ArrayBugTest() {
  string variationName;
  vector<int> A, expected;
  int B;

  variationName = "ex0";
  A = {};
  B = 100;
  expected = {};
  runTest(variationName, A, B, expected);

  variationName = "ex1";
  A = {0};
  B = 1;
  expected = {0};
  runTest(variationName, A, B, expected);

  variationName = "ex2";
  A = {0,1,2,3,4,5};
  B = 1;
  expected = {1,2,3,4,5,0};
  runTest(variationName, A, B, expected);

  variationName = "ex3";
  A = {0,1,2,3,4,5};
  B = 12;
  expected = {0,1,2,3,4,5};
  runTest(variationName, A, B, expected);

  variationName = "ex4";
  A = {0,1,2,3,4,5};
  B = 4;
  expected = {4,5,0,1,2,3};
  runTest(variationName, A, B, expected);
}
