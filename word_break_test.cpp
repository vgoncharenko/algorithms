//
// Created by Vitaliy on 2019-09-26.
//

#include "word_break.cpp"

void runTestWordBreak(std::string variationName, std::string s, std::vector<std::string> &wordDict, bool expected)
{
  WordBreak *solution = new WordBreak();
  double result = solution->wordBreak(s, wordDict);
  if (result != expected)
    std::cout << "FAIL " + variationName + ": WordBreak: \nresult: '" << result << "'\nexpected: '" << expected << "'"<< std::endl;
  else
    std::cout << variationName + " SUCCESS!" << std::endl;
}

void wordBreakTest() {
  std::string variationName;
  std::vector<std::string> wordDict;
  bool expected;
  std::string s;

  variationName = "ex0";
  wordDict = {};
  expected = false;
  s = "ABG";
    runTestWordBreak(variationName, s, wordDict, expected);

  variationName = "ex00";
  wordDict = {};
  expected = false;
  s = "";
    runTestWordBreak(variationName, s, wordDict, expected);

  variationName = "ex000";
  wordDict = {"mobile","samsung","sam",
              "sung","ma\n","mango",
              "icecream","and","go","i",
              "like","ice","cream"};
  expected = false;
  s = "";
    runTestWordBreak(variationName, s, wordDict, expected);

  variationName = "ex1";
  wordDict = {"mobile","samsung","sam",
                      "sung","ma\n","mango",
                      "icecream","and","go","i",
                      "like","ice","cream"};
  expected = true;
  s = "mobilesamsungmango";
    runTestWordBreak(variationName, s, wordDict, expected);

  variationName = "ex2";
  wordDict = {"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"};
  expected = false;
  s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";
    runTestWordBreak(variationName, s, wordDict, expected);

  variationName = "ex3";
  wordDict = {"a"};
  expected = true;
  s = "a";
    runTestWordBreak(variationName, s, wordDict, expected);

  variationName = "ex4";
  wordDict = {"a", "b"};
  expected = true;
  s = "ab";
    runTestWordBreak(variationName, s, wordDict, expected);
}
