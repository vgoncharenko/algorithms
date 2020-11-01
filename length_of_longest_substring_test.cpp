//
// Created by Vitaliy on 2019-09-25.
//

#include "length_of_longest_substring.cpp"

void testLengthOfLongestSubstring() {
  std::string input = "abcabcbb";
  int expected = 3;
  auto *solution = new lengthOfLongestSubstring();
  int result = solution->getLength(input);

  if (expected != result)
    std::cout << "FAIL: testSolutionOfSum: \nexpected: " << expected << "\nactual: " << result << std::endl;

  std::cout << '\n';


  input = "bbbbb";
  expected = 1;
  result = solution->getLength(input);

  if (expected != result)
    std::cout << "FAIL: testSolutionOfSum: \nexpected: " << expected << "\nactual: " << result << std::endl;

  std::cout << '\n';

  input = "pwwkew";
  expected = 3;
  result = solution->getLength(input);

  if (expected != result)
    std::cout << "FAIL: testSolutionOfSum: \nexpected: " << expected << "\nactual: " << result << std::endl;

  input = "pwket";
  expected = 5;
  result = solution->getLength(input);

  if (expected != result)
    std::cout << "FAIL: testSolutionOfSum: \nexpected: " << expected << "\nactual: " << result << std::endl;

  input = "erwpwkew";
  expected = 4;
  result = solution->getLength(input);

  if (expected != result)
    std::cout << "FAIL: testSolutionOfSum: \nexpected: " << expected << "\nactual: " << result << std::endl;

  input = "ynyo";
  expected = 3;
  result = solution->getLength(input);

  if (expected != result)
    std::cout << "FAIL: testSolutionOfSum: \nexpected: " << expected << "\nactual: " << result << std::endl;


  input = "bpfbhmipx";
  expected = 7;
  result = solution->getLength(input);

  if (expected != result)
    std::cout << "FAIL: testSolutionOfSum: \nexpected: " << expected << "\nactual: " << result << std::endl;

  input = "abcdbzkb";
  expected = 5;
  result = solution->getLength(input);

  if (expected != result)
    std::cout << "FAIL: testSolutionOfSum: \nexpected: " << expected << "\nactual: " << result << std::endl;

  std::cout << '\n';
}