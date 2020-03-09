//
// Created by Vitaliy on 2019-09-26.
//

#include "rotting-oranges.h"

void runRottingOrangesTest(string &variationName, vector<vector<int>>& grid, int expected) {
  RottingOranges *solution = new RottingOranges();
  int result = solution->orangesRotting(grid);
  if (result != expected)
    cout << "FAIL " + variationName + ": RottingOranges: \nresult: '" << result << "'\nexpected: '" << expected << "'"<< endl;
  else
    cout << variationName + " SUCCESS!" << endl;
}

void rottingOrangesTest() {
  string variationName;
  vector<vector<int>> grid;
  int expected;

  variationName = "ex0";
  grid = {{2,1,1},{1,1,0},{0,1,1}};
  expected = 4;
  runRottingOrangesTest(variationName, grid, expected);

  variationName = "ex1";
  grid = {{2,1,1},{0,1,1},{1,0,1}};
  expected = -1;
  runRottingOrangesTest(variationName, grid, expected);

}
