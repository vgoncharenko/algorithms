//
// Created by Vitaliy on 2019-09-23.
// https://leetcode.com/problems/top-k-frequent-words/
//

#include "top_k_frequent_word.h"

void testTopKFrequentWords() {
  std::vector<std::string> input = {"i", "love", "leetcode", "i", "love", "coding", "love", "coding", "coding", "coding"};
  std::vector<std::string> expected = {"coding", "love"};
  auto *solution = new TopKFrequentWords();
  std::vector<std::string> result = solution->topKFrequent(input, 2);
  for (int i = 0; i < result.size(); i++)
    if (expected[i] != result[i])
      std::cout << "FAIL: testTopKFrequentWords: \nexpected: " << expected[i] << "\nactual: " << result[i] << std::endl;

  std::cout << '\n';
}
