//
// Created by Vitaliy on 2019-09-25.
// https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
//

#ifndef TREE_CONSTRUCT_BINARY_TREE_FROM_PREORDER_AND_INORDER_TRAVERSAL_H
#define TREE_CONSTRUCT_BINARY_TREE_FROM_PREORDER_AND_INORDER_TRAVERSAL_H

#include <vector>
#include <sstream>
#include <queue>
#include "treeHelper.cpp"

class ConstructBinaryTreeFromPreorderAndInorderTraversal {
public:
    TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder);
};

#endif //TREE_CONSTRUCT_BINARY_TREE_FROM_PREORDER_AND_INORDER_TRAVERSAL_H
