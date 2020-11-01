//
// Created by Vitaliy on 2019-09-26.
//

#include "rotting-oranges.cpp"

void runRottingOrangesTest(std::string &variationName, std::vector<std::vector<int>>& grid, int expected) {
  RottingOranges *solution = new RottingOranges();
  int result = solution->orangesRotting(grid);
  if (result != expected)
    std::cout << "FAIL " + variationName + ": RottingOranges: \nresult: '" << result << "'\nexpected: '" << expected << "'"<< std::endl;
  else
    std::cout << variationName + " SUCCESS!" << std::endl;
}

void rottingOrangesTest() {
  std::string variationName;
  std::vector<std::vector<int>> grid;
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
