//
// Created by Vitaliy on 2019-09-26.
//

#include "word_search.cpp"

void runTestWordSearch(std::string variationName, std::vector<std::vector<char>>& grid, const std::string& word, bool expected)
{
  WordSearch *solution = new WordSearch();
  double result = solution->exist(grid, word);
  if (result != expected)
    std::cout << "FAIL " + variationName + ": WordSearch: \nresult: '" << result << "'\nexpected: '" << expected << "'"<< std::endl;
  else
    std::cout << variationName + " SUCCESS!" << std::endl;
}

void wordSearchTest() {
  std::string variationName;
  std::vector<std::vector<char>> grid;
  bool expected;
  std::string word;

  variationName = "ex0";
  grid = {{}};
  expected = false;
  word = "ABG";
    runTestWordSearch(variationName, grid, word, expected);

  variationName = "ex1";
  grid = {};
  expected = false;
  word = "ABG";
    runTestWordSearch(variationName, grid, word, expected);

  variationName = "ex2";
  grid = {{'A'}};
  expected = false;
  word = "ABG";
    runTestWordSearch(variationName, grid, word, expected);

  variationName = "ex3";
  grid = {{'A','B','C','D','E'},
          {'F','G','K','L','M'}};
  expected = true;
  word = "ABG";
    runTestWordSearch(variationName, grid, word, expected);

  variationName = "ex4";
  grid = {{'A','B','C','D','E'},
          {'F','G','K','L','M'}};
  expected = true;
  word = "ABGKCDL";
    runTestWordSearch(variationName, grid, word, expected);

  variationName = "ex5";
  grid = {{'A','B','C','D','E'},
          {'F','G','K','L','M'}};
  expected = false;
  word = "ABGKCDLZ";
    runTestWordSearch(variationName, grid, word, expected);

  variationName = "ex6";
  grid = {{'A','A'}};
  expected = false;
  word = "AAA";
    runTestWordSearch(variationName, grid, word, expected);

  variationName = "ex7";
  grid = {{'C','A', 'A'},
          {'A', 'A', 'A'},
          {'B', 'C', 'D'}};
  expected = true;
  word = "AAB";
    runTestWordSearch(variationName, grid, word, expected);
}
