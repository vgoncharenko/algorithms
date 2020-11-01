//
// Created by Vitaliy on 2019-09-26.
//

#include "spiral-order-matrix-i.cpp"

void runTestSpiralOrderMatrix(std::string &variationName, std::vector<std::vector<int>> &A, std::vector<int> &expected) {
  SpiralOrderMatrixI *solution = new SpiralOrderMatrixI();
  std::vector<int> result = solution->spiralOrder(A);
  if (result.size() != expected.size()) {
    std::cout << variationName + " FAIL size!" << "\nexpected:" << expected.size() << "\nresult:" << result.size() << std::endl;
  }
  for (int i = 0; i < expected.size(); ++i) {
    if (expected[i] != result[i])
      std::cout << "FAIL " + variationName + ": SpiralOrderMatrixI: \nresult[" << i << "] = '" << result[i] << "'\nexpected[" << i << "] = '" << expected[i] << "'" << std::endl;
  }
  std::cout << variationName + " SUCCESS!" << std::endl;
}

void spiralOrderMatrixITest() {
  std::string variationName;
  std::vector<std::vector<int>> A;
  std::vector<int> expected;

  variationName = "ex0";
  A = {};
  expected = {};
    runTestSpiralOrderMatrix(variationName, A, expected);

  variationName = "ex1";
  A = {{1,2,3},{4,5,6},{7,8,9}};
  expected = {1,2,3,6,9,8,7,4,5};
    runTestSpiralOrderMatrix(variationName, A, expected);

  variationName = "ex2";
  A = {{1,2,3}};
  expected = {1,2,3};
    runTestSpiralOrderMatrix(variationName, A, expected);

  variationName = "ex3";
  A = {{1,2,3},{4,5,6}};
  expected = {1,2,3,6,5,4};
    runTestSpiralOrderMatrix(variationName, A, expected);

  variationName = "ex4";
  A = {{1},{2},{3}};
  expected = {1,2,3};
    runTestSpiralOrderMatrix(variationName, A, expected);
}
