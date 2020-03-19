//
// Created by Vitaliy on 2019-09-23.
// https://leetcode.com/problems/maximum-width-of-binary-tree
//

using namespace std;

class MaximumWidthOfBinaryTree {
public:
    map<int,uint32_t> leftMostPositionPerLvl;
    uint32_t maxW = 0;

    int widthOfBinaryTree(TreeNode* root) {
      if (root == nullptr)
        return 0;

      h(root, 0, 0);

      return maxW;
    }

    void h (TreeNode* node, int depth, uint32_t pos) {
      if (node == nullptr)
        return;

      auto tmp = leftMostPositionPerLvl.insert({depth, pos});

      maxW = max(maxW, pos - tmp.first->second + 1);

      h(node->left, depth+1, pos*2);
      h(node->right, depth+1, pos*2+1);
    }

     int widthOfBinaryTree2(TreeNode* root) {
         if (root == nullptr)
             return 0;

         int maxW = 1, W = 0, WW = 0;
         bool hasNode = false;
         queue<TreeNode*> curQ, nextQ;
         curQ.push(root);
         while(!curQ.empty()) {
             root = curQ.front();
             curQ.pop();

             if (root) {
                 if (hasNode)
                    WW = W+1;

                 hasNode = true;
                 nextQ.push(root->left);
                 nextQ.push(root->right);
             } else if (root == nullptr && hasNode) {
                 nextQ.push(nullptr);
                 nextQ.push(nullptr);
             }

             if (hasNode)
                 W++;

             if (curQ.empty() && !nextQ.empty()) {
                 maxW = max(maxW, WW);
                 W = 0;
                 WW = 0;
                 hasNode = false;
                 curQ.swap(nextQ);
             }
         }

         return maxW;
     }
};
