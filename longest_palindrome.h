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
#include "max_heap.h"

using namespace std;

class LongestPalindrome {
    int checkIndexesCorrelation(vector<int> &v1, vector<int> &v2);
public:
    string find(string s);
    string find2(string s);
};


#endif //TREE_LONGEST_PALINDROME_H
