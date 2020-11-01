//
// Created by Vitaliy on 2019-09-23.
//

#include "find_elements_equelse_to_sum.cpp"

void testSolutionOfSum ()
{
  std::vector<int> vecOfNums = { 33, 45, 54, 1, 3, 7, 8, 22, 43, 19 };
  std::vector<int> expected = { 3, 6 };
  int target = 9;
  auto * solution = new SolutionOfSum();
  std::vector<int> result = solution->twoSum(vecOfNums, target);

  for (int i = 0; i < result.size(); i++)
    if (expected[i] != result[i])
      std::cout << "FAIL: testSolutionOfSum: \nexpected: " << expected[i] << "\nactual: " << result[i] << std::endl;

  std::cout << '\n';
}
