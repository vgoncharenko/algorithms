//
// Created by Vitaliy on 2019-09-25.
// https://leetcode.com/problems/validate-binary-search-tree/
//

#ifndef TREE_VALIDATE_BINARY_SEARCH_TREE_H
#define TREE_VALIDATE_BINARY_SEARCH_TREE_H

#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <queue>
#include <iostream>



//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class ValidateBinarySearchTree {
public:
    bool isValidBST(TreeNode* root);
};

#endif //TREE_VALIDATE_BINARY_SEARCH_TREE_H
