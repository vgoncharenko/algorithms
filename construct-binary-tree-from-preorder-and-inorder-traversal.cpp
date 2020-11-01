//
// Created by Vitaliy on 2019-09-25.
//

#include "construct-binary-tree-from-preorder-and-inorder-traversal.h"

void h(TreeNode *root, std::vector<int> &preorder, int preorderIndex, std::vector<int> &inorder, int inorderStart, int inorderEnd) {
  for (int i = inorderStart; i <= inorderEnd; ++i) {
    if (inorder[i] == root->val) {
      if (inorderStart <= i - 1 && preorderIndex + 1 <= preorder.size() - 1) {
        root->left = new TreeNode(preorder[preorderIndex + 1]);
        h(root->left, preorder, preorderIndex + 1, inorder, inorderStart, i - 1);
      }
      if (i + 1 <= inorderEnd && preorderIndex + i + 1 - inorderStart <= preorder.size() - 1) {
        root->right = new TreeNode(preorder[preorderIndex + i + 1 - inorderStart]);
        h(root->right, preorder, preorderIndex + i + 1 - inorderStart, inorder, i + 1, inorderEnd);
      }

      return;
    }
  }
}

struct TreeNode* ConstructBinaryTreeFromPreorderAndInorderTraversal::buildTree(std::vector<int> &preorder, std::vector<int> &inorder) {
  if (preorder.size() == 0 || inorder.size() == 0) {
    return nullptr;
  }
  TreeNode *root = new TreeNode(preorder[0]);
  h(root, preorder, 0, inorder, 0, inorder.size() - 1);

  return root;
}
