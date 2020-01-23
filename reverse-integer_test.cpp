//
// Created by Vitaliy on 2019-09-26.
//

#include "reverse-integer.h"

void runReverseIntegerTest(string &variationName, int x, int expected) {
  ReverseInteger *solution = new ReverseInteger();
  int result = solution->reverse(x);
  if (result != expected)
    cout << "FAIL " + variationName + ": ReverseInteger: \nresult: '" << result << "'\nexpected: '" << expected << "'"<< endl;
  else
    cout << variationName + " SUCCESS!" << endl;
}

void reverseIntegerTest() {
  string variationName;
  int x, expected;

  variationName = "ex0";
  x = 0;
  expected = 0;
  runReverseIntegerTest(variationName, x, expected);

  variationName = "ex1";
  x = 1;
  expected = 1;
  runReverseIntegerTest(variationName, x, expected);

  variationName = "ex2";
  x = 20;
  expected = 2;
  runReverseIntegerTest(variationName, x, expected);

  variationName = "ex3";
  x = 321;
  expected = 123;
  runReverseIntegerTest(variationName, x, expected);

  variationName = "ex4";
  x = -4098;
  expected = -8904;
  runReverseIntegerTest(variationName, x, expected);

  variationName = "ex5";
  x = 1000000003;
  expected = 0;
  runReverseIntegerTest(variationName, x, expected);

  variationName = "ex6";
  x = -1000000003;
  expected = 0;
  runReverseIntegerTest(variationName, x, expected);
}
