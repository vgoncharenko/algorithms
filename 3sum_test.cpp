//
// Created by Vitaliy on 2019-09-26.
//

#include "3sum.cpp"

void runSum3Test(std::string variationName, std::vector<int> &A, std::vector<std::vector<int>> &expected)
{
  Sum3 *solution = new Sum3();
  std::vector<std::vector<int>> result = solution->threeSum(A);
  for (int i = 0; i < expected.size(); ++i) {
    for (int j = 0; j < 2; ++j) {
      if (expected[i][j] != result[i][j])
        std::cout << "FAIL " + variationName + ": Sum3: \nresult[" << i << "][" << j << "] = '" << result[i][j] << "'\nexpected[" << i << "][" << j << "] = '" << expected[i][j] << "'" << std::endl;
    }
  }
  std::cout << variationName + " SUCCESS!" << std::endl;
}

void Sum3Test() {
  std::string variationName;
  std::vector<int> A;
  std::vector<std::vector<int>> expected;

  variationName = "ex0";
  A = {-1,0,1,2,-1,-4};
  expected = {
          {-1, -1, 2},
          {-1, 0, 1},
  };
  runSum3Test(variationName, A, expected);
}
