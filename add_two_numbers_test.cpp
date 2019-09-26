//
// Created by Vitaliy on 2019-09-25.
//

#include "add_two_numbers.h"

void testAddTwoNumbers()
{
  // ex1
  vector <int> input1 = {2, 4, 3};
  vector <int> input2 = {5, 6, 4};
  vector <int> expected = {7, 0, 8};

  auto *sumator = new AddTwoNumbers();
  vector <int> output = sumator->sum(input1, input2);

  for (int i = 0; i < output.size(); i++)
    if (expected[i] != output[i])
      cout << "FAIL: testAddTwoNumbers: \nexpected: " << expected[i] << "\nactual: " << output[i] << endl;

  // ex2
  input1 = {3, 4, 9};
  input2 = {5, 6, 9};
  expected = {8, 0, 9, 1};

  output = sumator->sum(input1, input2);

  for (int i = 0; i < output.size(); i++)
    if (expected[i] != output[i])
      cout << "FAIL: testAddTwoNumbers: \nexpected: " << expected[i] << "\nactual: " << output[i] << endl;

  // ex3
  input1 = {3, 4};
  input2 = {5, 6, 9};
  expected = {8, 0, 0, 1};

  output = sumator->sum(input1, input2);

  for (int i = 0; i < output.size(); i++)
    if (expected[i] != output[i])
      cout << "FAIL: testAddTwoNumbers: \nexpected: " << expected[i] << "\nactual: " << output[i] << endl;
}