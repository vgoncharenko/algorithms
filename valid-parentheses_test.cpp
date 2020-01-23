//
// Created by Vitaliy on 2019-09-26.
//

#include "valid-parentheses.h"

void runValidParenthesesTest(string &variationName, string s, bool expected) {
  ValidParentheses *solution = new ValidParentheses();
  int result = solution->isValid(s);
  if (result != expected)
    cout << "FAIL " + variationName + ": ValidParentheses: \nresult: '" << result << "'\nexpected: '" << expected << "'"<< endl;
  else
    cout << variationName + " SUCCESS!" << endl;
}

void validParenthesesTest() {
  string variationName;
  string s;
  bool expected;

  variationName = "ex0";
  s = "";
  expected = true;
  runValidParenthesesTest(variationName, s, expected);

  variationName = "ex1";
  s = "[]";
  expected = true;
  runValidParenthesesTest(variationName, s, expected);

  variationName = "ex2";
  s = "[{}{}{}{}{[[[[[[[]()()()()()()()(((((())))))]]]]]]}]";
  expected = true;
  runValidParenthesesTest(variationName, s, expected);

  variationName = "ex3";
  s = "[{}{}{}{}{[[[[[[[]()()())()()()(((((())))))]]]]]]}]";
  expected = false;
  runValidParenthesesTest(variationName, s, expected);

  variationName = "ex4";
  s = "]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]()";
  expected = false;
  runValidParenthesesTest(variationName, s, expected);

  variationName = "ex5";
  s = "[";
  expected = false;
  runValidParenthesesTest(variationName, s, expected);
}
