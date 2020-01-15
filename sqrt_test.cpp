//
// Created by Vitaliy on 2019-09-26.
//

#include "sqrt.h"

void runTest(string &variationName, int x, int expected) {
  SQRT *solution = new SQRT();
  int result = solution->sqrt(x);
  if (result != expected)
    cout << "FAIL " + variationName + ": SQRT: \nresult: '" << result << "'\nexpected: '" << expected << "'"<< endl;
  else
    cout << variationName + " SUCCESS!" << endl;
}

void sqrtTest() {
  string variationName;
  int x, expected;

  variationName = "ex0";
  x = 0;
  expected = 0;
  runTest(variationName, x, expected);

  variationName = "ex1";
  x = 1;
  expected = 1;
  runTest(variationName, x, expected);

  variationName = "ex2";
  x = 2;
  expected = 1;
  runTest(variationName, x, expected);

  variationName = "ex3";
  x = 3;
  expected = 1;
  runTest(variationName, x, expected);

  variationName = "ex4";
  x = 4;
  expected = 2;
  runTest(variationName, x, expected);

  variationName = "ex5";
  x = 10;
  expected = 3;
  runTest(variationName, x, expected);

  variationName = "ex6";
  x = 12;
  expected = 3;
  runTest(variationName, x, expected);

  variationName = "ex7";
  x = 16;
  expected = 4;
  runTest(variationName, x, expected);
}
