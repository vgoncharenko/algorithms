//
// Created by Vitaliy on 2019-09-23.
//

#ifndef TREE_TOP_K_FREQUENT_WORD_H
#define TREE_TOP_K_FREQUENT_WORD_H

#include <iostream>
#include <vector>
#include <map>
#include "min_heap.cpp"
#include <string>
#include <iterator>
#include <queue>

class TopKFrequentWords {
public:
    std::vector<std::string> topKFrequent(std::vector<std::string> &words, int k);
};

#endif //TREE_TOP_K_FREQUENT_WORD_H
