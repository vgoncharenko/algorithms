//
// Created by Vitaliy on 2019-09-23.
// https://leetcode.com/problems/top-k-frequent-words/
//

#include "top_k_frequent_word.h"

vector<string> TopKFrequentWords::topKFrequent(std::vector<string> &words, int k) {
  vector<string> result;
  // prepare map
  map<string, uint8_t> myMap;
  for (string &word : words) {
    auto item = myMap.find(word);
    if (item == myMap.end()) {
      myMap.insert(pair<string, int>(word, 1));
    } else {
      item->second++;
    }
  }

  // Creates a Min heap of points (order by frequency coordinate)
  priority_queue<Term, vector<Term>, TermComparator> minHeap;
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
