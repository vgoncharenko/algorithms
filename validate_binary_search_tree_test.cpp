//
// Created by Vitaliy on 2019-09-26.
//

#include "validate_binary_search_tree.cpp"

void runTestValidateBinarySearchTree(std::string variationName, std::string &input, bool expected) {
  TreeNode *root = stringToTreeNode(input);
  ValidateBinarySearchTree *solution = new ValidateBinarySearchTree();
  bool result = solution->isValidBST(root);
  if (result != expected)
    std::cout << "FAIL " + variationName + ": ValidateBinarySearchTree: \nresult: '" << result << "'\nexpected: '"
         << expected << "'" << std::endl;
  else
    std::cout << variationName + " SUCCESS!" << std::endl;
}

void makeTree(TreeNode *current, std::vector<int> &input, int pos, int size) {
  if (pos >= size)
    return;

  if (0 != input[pos]) {
    current->left = new TreeNode(input[pos]);
    makeTree(current->left, input, pos * 2 + 1, size);
  }
  if (0 != input[pos + 1]) {
    current->right = new TreeNode(input[pos + 1]);
    makeTree(current->right, input, (pos + 1) * 2 + 1, size);
  }
}

void validateBinarySearchTreeTest() {
  std::string variationName;

  std::string input;
  bool expected;

  variationName = "ex0";
  input = "[]";
  expected = true;
    runTestValidateBinarySearchTree(variationName, input, expected);

  variationName = "ex1";
  input = "[2,1,8,null,null,3,5]";
  expected = false;
    runTestValidateBinarySearchTree(variationName, input, expected);

  variationName = "ex6";
  input = "[1,1]";
  expected = false;
    runTestValidateBinarySearchTree(variationName, input, expected);

  variationName = "ex7";
  input = "[2,1]";
  expected = true;
    runTestValidateBinarySearchTree(variationName, input, expected);

  variationName = "ex8";
  input = "[989,982,null,972,null,947,null,920,null,903,null,894,null,881,null,866,null,864,null,842,null,841,null,796,null,726,null,647,null,613,719,593,null,null,null,590,null,558,null,554,null,538,null,512,null,504,null,468,505,467,null,null,null,456,null,413,null,331,null,330,407,320,null,null,null,312,null,306,null,301,null,274,null,251,null,235,null,231,null,222,null,181,null,93,null,83,null,73,null,64,null,62,null,60,null,28,null,21,null,20,null,-32,null,-52,null,-70,null,-87,null,-98,null,-102,null,-115,null,-116,null,-139,null,-183,null,-224,null,-241,null,-263,null,-284,null,-294,null,-296,null,-320,null,-330,null,-392,null,-398,null,-407,null,-431,null,-445,null,-460,null,-463,null,-492,null,-507,null,-518,null,-539,null,-552,null,-558,null,-559,null,-587,null,-673,null,-736,null,-757,null,-766,null,-767,null,-823,null,-830,null,-867,null,-875,null,-891,null,-905,null,-910,null,-924,null,-960,null,-985,null,-988]";
  expected = true;
    runTestValidateBinarySearchTree(variationName, input, expected);
}
