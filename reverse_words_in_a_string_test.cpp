//
// Created by Vitaliy on 2019-09-26.
//

#include "reverse_words_in_a_string.h"

void runTestReverseWordsInAString(std::string variationName, std::string input, std::string expected)
{
  ReverseWordsInAString *solution = new ReverseWordsInAString();
  std::string result = solution->reverseWords(input);
  if (result != expected)
    std::cout << "FAIL " + variationName + ": testDeepCopyListWithRandomPointerTest: \nresult: '" << result << "'\nexpected: '" << expected << "'"<< std::endl;
  else
    std::cout << variationName + " SUCCESS!" << std::endl;
}

void reverseWordsInAStringTest() {
  std::string variationName,
         input,
         expected;

  variationName = "ex0";
  input = "";
  expected = "";
    runTestReverseWordsInAString(variationName, input, expected);

  variationName = "ex0.1";
  input = "       ";
  expected = "";
    runTestReverseWordsInAString(variationName, input, expected);

  variationName = "ex0.2";
  input = "  hello world!  ";
  expected = "world! hello";
    runTestReverseWordsInAString(variationName, input, expected);

  variationName = "ex1";
  input = "abc def ght";
  expected = "ght def abc";
    runTestReverseWordsInAString(variationName, input, expected);

  variationName = "ex2";
  input = "abcd ef g";
  expected = "g ef abcd";
    runTestReverseWordsInAString(variationName, input, expected);

  variationName = "ex3";
  input = " abc def ght ";
  expected = "ght def abc";
    runTestReverseWordsInAString(variationName, input, expected);

  variationName = "ex4";
  input = " abc   def   ght   ";
  expected = "ght def abc";
    runTestReverseWordsInAString(variationName, input, expected);

  variationName = "ex5";
  input = "def";
  expected = "def";
    runTestReverseWordsInAString(variationName, input, expected);

  variationName = "ex6";
  input = "d";
  expected = "d";
    runTestReverseWordsInAString(variationName, input, expected);

  variationName = "ex7";
  input = "         d";
  expected = "d";
    runTestReverseWordsInAString(variationName, input, expected);

  variationName = "ex8";
  input = "d         ";
  expected = "d";
    runTestReverseWordsInAString(variationName, input, expected);

  variationName = "ex8.1";
  input = "da         ";
  expected = "da";
    runTestReverseWordsInAString(variationName, input, expected);

  variationName = "ex9";
  input = "  def  ";
  expected = "def";
    runTestReverseWordsInAString(variationName, input, expected);

  variationName = "ex10";
  input = "  d e f  ";
  expected = "f e d";
    runTestReverseWordsInAString(variationName, input, expected);
}
