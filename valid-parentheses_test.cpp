//
// Created by Vitaliy on 2019-09-26.
//

#include "valid-parentheses.cpp"

void runValidParenthesesTest(std::string &variationName, std::string s, bool expected) {
  ValidParentheses *solution = new ValidParentheses();
  int result = solution->isValid(s);
  if (result != expected)
      std::cout << "FAIL " + variationName + ": ValidParentheses: \nresult: '" << result << "'\nexpected: '" << expected << "'"<< std::endl;
  else
      std::cout << variationName + " SUCCESS!" << std::endl;
}

void validParenthesesTest() {
  std::string variationName;
  std::string s;
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
