//
// Created by Vitaliy on 2019-09-25.
// https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
//

#ifndef TREE_CONSTRUCT_BINARY_TREE_FROM_PREORDER_AND_INORDER_TRAVERSAL_H
#define TREE_CONSTRUCT_BINARY_TREE_FROM_PREORDER_AND_INORDER_TRAVERSAL_H

#include <vector>

using namespace std;

struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class ConstructBinaryTreeFromPreorderAndInorderTraversal {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder);
};

#endif //TREE_CONSTRUCT_BINARY_TREE_FROM_PREORDER_AND_INORDER_TRAVERSAL_H
