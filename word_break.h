//
// Created by Vitaliy on 2019-09-25.
// https://leetcode.com/problems/word-break/
//

#ifndef TREE_WORD_BREAK_H
#define TREE_WORD_BREAK_H

#include <string>
#include <algorithm>
#include <vector>
#include "trie.h"

using namespace std;

class WordBreak {
public:
    bool wordBreak(string s, vector<string>& wordDict);
};

#endif //TREE_WORD_BREAK_H
