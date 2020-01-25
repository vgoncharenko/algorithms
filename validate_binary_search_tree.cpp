//
// Created by Vitaliy on 2019-09-25.
//

#include "validate_binary_search_tree.h"

bool check(TreeNode *current, map<uint64_t, int> &keys, uint64_t i, int l) {
  bool result = true;
  keys[i] = current->val;
  if (current->val != 0) {
    uint64_t temp = i,
            tempP;
    for (int ii = l; ii > 0; ii--) {
      if (temp % 2) {
        tempP = (temp - 1) / 2;
        if (keys[tempP] <= current->val)
          return false;
      } else {
        tempP = (temp - 2) / 2;
        if (keys[tempP] >= current->val)
          return false;
      }

      temp = tempP;
    }
  }
  l++;
  if (nullptr != current->left) {
    result = check(current->left, keys, i * 2 + 1, l);
    if (!result) return result;
  }
  if (nullptr != current->right) {
    result = check(current->right, keys, i * 2 + 2, l);
    if (!result) return result;
  }

  return result;
}

bool check2(TreeNode *current, int lh, int gh) {
  if ((lh != -1 && current->val >= lh) || (gh != -1 && current->val <= gh))
    return false;

  if (nullptr != current->left && !check2(current->left, current->val, gh)) {
      return false;
  }

  if (nullptr != current->right && !check2(current->right, lh, current->val)) {
      return false;
  }

  return true;
}

bool ValidateBinarySearchTree::isValidBST(struct TreeNode *root) {
  if (nullptr == root)
    return true;
  return check2(root, -1, -1);
}
