//
// Created by Vitaliy on 2019-09-23.
//

#ifndef TREE_TOP_K_FREQUENT_WORD_H
#define TREE_TOP_K_FREQUENT_WORD_H

#include <iostream>
#include <vector>
#include <map>
#include "min_heap.h"
#include <string>
#include <iterator>
#include <queue>

using namespace std;

class TopKFrequentWords {
public:
    vector<string> topKFrequent(std::vector<string> &words, int k);
};

#endif //TREE_TOP_K_FREQUENT_WORD_H
