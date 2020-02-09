//
// Created by Vitaliy on 2019-09-26.
//

#include "3sum.h"

void runSum3Test(string variationName, vector<int> &A, vector<vector<int>> &expected)
{
  Sum3 *solution = new Sum3();
  vector<vector<int>> result = solution->threeSum(A);
  for (int i = 0; i < expected.size(); ++i) {
    for (int j = 0; j < 2; ++j) {
      if (expected[i][j] != result[i][j])
        cout << "FAIL " + variationName + ": Sum3: \nresult[" << i << "][" << j << "] = '" << result[i][j] << "'\nexpected[" << i << "][" << j << "] = '" << expected[i][j] << "'" << endl;
    }
  }
  cout << variationName + " SUCCESS!" << endl;
}

void Sum3Test() {
  string variationName;
  vector<int> A;
  vector<vector<int>> expected;

  variationName = "ex0";
  A = {-1,0,1,2,-1,-4};
  expected = {
          {-1, -1, 2},
          {-1, 0, 1},
  };
  runSum3Test(variationName, A, expected);
}
