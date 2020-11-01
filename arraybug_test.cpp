//
// Created by Vitaliy on 2019-09-26.
//

#include "arraybug.h"

void runTestArrayBug(std::string variationName, std::vector<int> &A, int B, std::vector<int> &expected)
{
  ArrayBug *solution = new ArrayBug();
  std::vector<int> result = solution->rotateArray(A, B);
  for (int i = 0; i < expected.size(); ++i) {
    if (expected[i] != result[i])
      std::cout << "FAIL " + variationName + ": MaxSet: \nresult[" << i << "] = '" << result[i] << "'\nexpected[" << i << "] = '" << expected[i] << "'" << std::endl;
  }
  std::cout << variationName + " SUCCESS!" << std::endl;
}

void ArrayBugTest() {
  std::string variationName;
  std::vector<int> A, expected;
  int B;

  variationName = "ex0";
  A = {};
  B = 100;
  expected = {};
    runTestArrayBug(variationName, A, B, expected);

  variationName = "ex1";
  A = {0};
  B = 1;
  expected = {0};
    runTestArrayBug(variationName, A, B, expected);

  variationName = "ex2";
  A = {0,1,2,3,4,5};
  B = 1;
  expected = {1,2,3,4,5,0};
    runTestArrayBug(variationName, A, B, expected);

  variationName = "ex3";
  A = {0,1,2,3,4,5};
  B = 12;
  expected = {0,1,2,3,4,5};
    runTestArrayBug(variationName, A, B, expected);

  variationName = "ex4";
  A = {0,1,2,3,4,5};
  B = 4;
  expected = {4,5,0,1,2,3};
    runTestArrayBug(variationName, A, B, expected);
}
