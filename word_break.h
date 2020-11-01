//
// Created by Vitaliy on 2019-09-25.
// https://leetcode.com/problems/word-break/
// https://www.youtube.com/watch?v=WepWFGxiwRs
//

#ifndef TREE_WORD_BREAK_H
#define TREE_WORD_BREAK_H

#include <string>
#include <algorithm>
#include <vector>
#include "trie.h"

class WordBreak {
public:
    bool wordBreak(std::string s, std::vector<std::string>& wordDict);
};

#endif //TREE_WORD_BREAK_H
