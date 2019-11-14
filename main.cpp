#include <iostream>
#include "b_tree_test.cpp"
#include "find_elements_equelse_to_sum_test.cpp"
#include "top_k_frequent_word_test.cpp"
#include "add_two_numbers_test.cpp"
#include "length_of_longest_substring_test.cpp"
#include "find_median_sorted_arrays_test.cpp"
#include "longest_palindrome_test.cpp"

int main() {
  testBTree();
  testSolutionOfSum();
  testTopKFrequentWords();
  testAddTwoNumbers();
  testAddTwoNumbers2();
  testLengthOfLongestSubstring();
//  testFindMedianSortedArrays();
  testLongestPalindrome();

  cout << "SUCCESS!" << endl;
  return 0;
}
