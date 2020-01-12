//
// Created by Vitaliy on 2019-09-26.
//

#include "word_break.h"

void runTest(string variationName, string s, vector<string> &wordDict, bool expected)
{
  WordBreak *solution = new WordBreak();
  double result = solution->wordBreak(s, wordDict);
  if (result != expected)
    cout << "FAIL " + variationName + ": WordBreak: \nresult: '" << result << "'\nexpected: '" << expected << "'"<< endl;
  else
    cout << variationName + " SUCCESS!" << endl;
}

void wordBreakTest() {
  string variationName;
  vector<string> wordDict;
  bool expected;
  string s;

  variationName = "ex0";
  wordDict = {};
  expected = false;
  s = "ABG";
  runTest(variationName, s, wordDict, expected);

  variationName = "ex00";
  wordDict = {};
  expected = false;
  s = "";
  runTest(variationName, s, wordDict, expected);

  variationName = "ex000";
  wordDict = {"mobile","samsung","sam",
              "sung","ma\n","mango",
              "icecream","and","go","i",
              "like","ice","cream"};
  expected = false;
  s = "";
  runTest(variationName, s, wordDict, expected);

  variationName = "ex1";
  wordDict = {"mobile","samsung","sam",
                      "sung","ma\n","mango",
                      "icecream","and","go","i",
                      "like","ice","cream"};
  expected = true;
  s = "mobilesamsungmango";
  runTest(variationName, s, wordDict, expected);

  variationName = "ex2";
  wordDict = {"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"};
  expected = false;
  s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";
  runTest(variationName, s, wordDict, expected);

  variationName = "ex3";
  wordDict = {"a"};
  expected = true;
  s = "a";
  runTest(variationName, s, wordDict, expected);

  variationName = "ex4";
  wordDict = {"a", "b"};
  expected = true;
  s = "ab";
  runTest(variationName, s, wordDict, expected);
}
