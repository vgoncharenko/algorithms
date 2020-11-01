//
// Created by Vitaliy on 2019-09-26.
// https://leetcode.com/problems/longest-palindromic-substring
//

#ifndef TREE_LONGEST_PALINDROME_H
#define TREE_LONGEST_PALINDROME_H

#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <queue>
#include "max_heap.cpp"

class LongestPalindrome {
    int checkIndexesCorrelation(std::vector<int> &v1, std::vector<int> &v2);
public:
    std::string find(std::string s);
    std::string find2(std::string s);
    std::string find3(std::string s);
};


#endif //TREE_LONGEST_PALINDROME_H
