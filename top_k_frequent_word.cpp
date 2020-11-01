//
// Created by Vitaliy on 2019-09-23.
// https://leetcode.com/problems/top-k-frequent-words/
//

#include "top_k_frequent_word.h"

std::vector<std::string> TopKFrequentWords::topKFrequent(std::vector<std::string> &words, int k) {
  std::vector<std::string> result;
  // prepare map
    std::map<std::string, uint8_t> myMap;
  for (std::string &word : words) {
    auto item = myMap.find(word);
    if (item == myMap.end()) {
      myMap.insert(std::pair<std::string, int>(word, 1));
    } else {
      item->second++;
    }
  }

  // Creates a Min heap of points (order by frequency coordinate)
    std::priority_queue<Term, std::vector<Term>, TermComparator> minHeap;
  // prepare min heap
  auto item = myMap.begin();
  while (item != myMap.end()) {
    minHeap.push(Term(item->first, item->second));
    item++;
    while (minHeap.size() > k) {
      minHeap.pop();
    }
  }

  while (!minHeap.empty()) {
    result.insert(result.begin(), minHeap.top().term);
    minHeap.pop();
  }

  return result;
}
