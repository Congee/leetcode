#ifdef __LOCAL__
#include <leetcode.h>
#endif

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
 public:
  // -----> root
  // <----
  // ---->
  vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    if (root == nullptr) return {};

    vector<vector<int>> vec;

    std::deque<TreeNode*> dq;
    dq.push_back(root);
    bool left_to_right = true;

    while (dq.size()) {
      int len = dq.size();

      vec.push_back({});
      if (left_to_right) {
        for (auto&& node : dq) vec.back().push_back(node->val);
      } else {
        for (auto it = dq.rbegin(); it != dq.rend(); ++it)
          vec.back().push_back((*it)->val);
      }

      for (int i = 0; i < len; ++i) {
        auto node = dq.front();
        dq.pop_front();

        if (node->left) dq.push_back(node->left);
        if (node->right) dq.push_back(node->right);
      }

      left_to_right = !left_to_right;
    }

    return vec;
  }
};
