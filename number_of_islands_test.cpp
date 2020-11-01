//
// Created by Vitaliy on 2019-09-26.
//

#include "number_of_islands.h"

void runTest(std::string variationName, std::vector<std::vector<char>>& grid, int expected)
{
  NumberOfIslands *solution = new NumberOfIslands();
  double result = solution->numIslands(grid);
  if (result != expected)
    std::cout << "FAIL " + variationName + ": NumberOfIslands: \nresult: '" << result << "'\nexpected: '" << expected << "'"<< std::endl;
  else
    std::cout << variationName + " SUCCESS!" << std::endl;
}

void numberOfIslandsTest() {
  std::string variationName;
  std::vector<std::vector<char>> grid;
  int expected;

  variationName = "ex0";
  grid = {{'1','1','1','1','1'},
          {'1','1','1','1','1'}};
  expected = 1;
  runTest(variationName, grid, expected);

  variationName = "ex1";
  grid = {{'1'}};
  expected = 1;
  runTest(variationName, grid, expected);

  variationName = "ex2";
  grid = {{'0','0','0','0','0'},
          {'0','0','0','0','0'}};
  expected = 0;
  runTest(variationName, grid, expected);

  variationName = "ex3";
  grid = {{'0'}};
  expected = 0;
  runTest(variationName, grid, expected);

  variationName = "ex4";
  grid = {{'1','1','1','1','0'},
          {'1','1','0','1','0'},
          {'1','1','0','0','0'},
          {'0','0','0','0','0'}};
  expected = 1;
  runTest(variationName, grid, expected);

  variationName = "ex5";
  grid = {{'1','1','0','0','0'},
          {'1','1','0','0','0'},
          {'0','0','1','0','0'},
          {'0','0','0','1','1'}};
  expected = 3;
  runTest(variationName, grid, expected);

  variationName = "ex6";
  grid = {{}};
  expected = 0;
  runTest(variationName, grid, expected);

  variationName = "ex7";
  grid = {};
  expected = 0;
  runTest(variationName, grid, expected);
}
