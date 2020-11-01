//
// Created by Vitaliy on 2019-09-25.
//

#include "construct-binary-tree-from-preorder-and-inorder-traversal.h"

void
h(TreeNode *root, std::vector<int> &preorder, int preorderIndex, std::vector<int> &inorder, int inorderStart, int inorderEnd) {
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

void trimLeftTrailingSpaces(std::string &input) {
  input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
      return !isspace(ch);
  }));
}

void trimRightTrailingSpaces(std::string &input) {
  input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
      return !isspace(ch);
  }).base(), input.end());
}

std::vector<int> stringToIntegerVector(std::string input) {
  std::vector<int> output;
  trimLeftTrailingSpaces(input);
  trimRightTrailingSpaces(input);
  input = input.substr(1, input.length() - 2);
  std::stringstream ss;
  ss.str(input);
  std::string item;
  char delim = ',';
  while (getline(ss, item, delim)) {
    output.push_back(stoi(item));
  }
  return output;
}

std::string treeNodeToString(TreeNode *root) {
  if (root == nullptr) {
    return "[]";
  }

  std::string output = "";
  std::queue < TreeNode * > q;
  q.push(root);
  while (!q.empty()) {
    TreeNode *node = q.front();
    q.pop();

    if (node == nullptr) {
      output += "null, ";
      continue;
    }

    output += std::to_string(node->val) + ", ";
    q.push(node->left);
    q.push(node->right);
  }
  return "[" + output.substr(0, output.length() - 2) + "]";
}
