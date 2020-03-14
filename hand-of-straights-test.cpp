//
// Created by Vitaliy on 2019-09-26.
//

#include "hand-of-straights.h"

void runTestHandOfStraights(string variationName, bool expected, vector<int> hand, int W) {
  auto solution = new HandOfStraights();
  bool result = solution->isNStraightHand(hand, W);

  if (result != expected)
    cout << variationName << " FAIL; "<< endl;
  else
    cout << variationName + " SUCCESS!" << endl;
}

void testHandOfStraightsTest() {
  string variationName;
  bool expected, result;

  vector<int> hand;
  int W;

  variationName = "ex0";
  hand = {1,2,3,6,2,3,4,7,8};
  W = 3;
  expected = true;
  runTestHandOfStraights(variationName, expected, hand, W);

  variationName = "ex1";
  hand = {1,2,3,4,5};
  W = 4;
  expected = false;
  runTestHandOfStraights(variationName, expected, hand, W);

  variationName = "ex2";
  hand = {1,2,3,6,2,3,4,7,9};
  W = 3;
  expected = false;
  runTestHandOfStraights(variationName, expected, hand, W);

  variationName = "ex3";
  hand = {2,2,2,2,2,2,2,2,2};
  W = 3;
  expected = false;
  runTestHandOfStraights(variationName, expected, hand, W);

  variationName = "ex4";
  hand = {2,2,2,2,2,2,2,2,2};
  W = 1;
  expected = true;
  runTestHandOfStraights(variationName, expected, hand, W);
}
