//
// Created by Vitaliy on 2019-09-26.
//

#include "reverse_words_in_a_string.h"

void runTest(string variationName, string input, string expected)
{
  ReverseWordsInAString *solution = new ReverseWordsInAString();
  string result = solution->reverseWords(input);
  if (result != expected)
    cout << "FAIL " + variationName + ": testDeepCopyListWithRandomPointerTest: \nresult: '" << result << "'\nexpected: '" << expected << "'"<< endl;
  else
    cout << variationName + " SUCCESS!" << endl;
}

void reverseWordsInAStringTest() {
  string variationName,
         input,
         expected;

  variationName = "ex0";
  input = "";
  expected = "";
  runTest(variationName, input, expected);

  variationName = "ex0.1";
  input = "       ";
  expected = "";
  runTest(variationName, input, expected);

  variationName = "ex0.2";
  input = "  hello world!  ";
  expected = "world! hello";
  runTest(variationName, input, expected);

  variationName = "ex1";
  input = "abc def ght";
  expected = "ght def abc";
  runTest(variationName, input, expected);

  variationName = "ex2";
  input = "abcd ef g";
  expected = "g ef abcd";
  runTest(variationName, input, expected);

  variationName = "ex3";
  input = " abc def ght ";
  expected = "ght def abc";
  runTest(variationName, input, expected);

  variationName = "ex4";
  input = " abc   def   ght   ";
  expected = "ght def abc";
  runTest(variationName, input, expected);

  variationName = "ex5";
  input = "def";
  expected = "def";
  runTest(variationName, input, expected);

  variationName = "ex6";
  input = "d";
  expected = "d";
  runTest(variationName, input, expected);

  variationName = "ex7";
  input = "         d";
  expected = "d";
  runTest(variationName, input, expected);

  variationName = "ex8";
  input = "d         ";
  expected = "d";
  runTest(variationName, input, expected);

  variationName = "ex8.1";
  input = "da         ";
  expected = "da";
  runTest(variationName, input, expected);

  variationName = "ex9";
  input = "  def  ";
  expected = "def";
  runTest(variationName, input, expected);

  variationName = "ex10";
  input = "  d e f  ";
  expected = "f e d";
  runTest(variationName, input, expected);
}
