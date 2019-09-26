#include <iostream>
#include "b_tree_test.cpp"
#include "find_elements_equelse_to_sum_test.cpp"
#include "top_k_frequent_word_test.cpp"
#include "add_two_numbers_test.cpp"

int main() {
  testBTree();
  testSolutionOfSum();
  testTopKFrequentWords();
  testAddTwoNumbers();

  cout << "SUCCESS!" << endl;

  return 0;
}