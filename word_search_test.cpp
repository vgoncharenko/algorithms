//
// Created by Vitaliy on 2019-09-26.
//

#include "word_search.h"

void runTest(string variationName, vector<vector<char>>& grid, const string& word, bool expected)
{
  WordSearch *solution = new WordSearch();
  double result = solution->exist(grid, word);
  if (result != expected)
    cout << "FAIL " + variationName + ": WordSearch: \nresult: '" << result << "'\nexpected: '" << expected << "'"<< endl;
  else
    cout << variationName + " SUCCESS!" << endl;
}

void wordSearchTest() {
  string variationName;
  vector<vector<char>> grid;
  bool expected;
  string word;

  variationName = "ex0";
  grid = {{}};
  expected = false;
  word = "ABG";
  runTest(variationName, grid, word, expected);

  variationName = "ex1";
  grid = {};
  expected = false;
  word = "ABG";
  runTest(variationName, grid, word, expected);

  variationName = "ex2";
  grid = {{'A'}};
  expected = false;
  word = "ABG";
  runTest(variationName, grid, word, expected);

  variationName = "ex3";
  grid = {{'A','B','C','D','E'},
          {'F','G','K','L','M'}};
  expected = true;
  word = "ABG";
  runTest(variationName, grid, word, expected);

  variationName = "ex4";
  grid = {{'A','B','C','D','E'},
          {'F','G','K','L','M'}};
  expected = true;
  word = "ABGKCDL";
  runTest(variationName, grid, word, expected);

  variationName = "ex5";
  grid = {{'A','B','C','D','E'},
          {'F','G','K','L','M'}};
  expected = false;
  word = "ABGKCDLZ";
  runTest(variationName, grid, word, expected);

  variationName = "ex6";
  grid = {{'A','A'}};
  expected = false;
  word = "AAA";
  runTest(variationName, grid, word, expected);

  variationName = "ex7";
  grid = {{'C','A', 'A'},
          {'A', 'A', 'A'},
          {'B', 'C', 'D'}};
  expected = true;
  word = "AAB";
  runTest(variationName, grid, word, expected);
}
