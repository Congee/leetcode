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
  TreeNode* addOneRow(TreeNode* root, int val, int depth) {
    if (depth == 1) {
      return new TreeNode(val, root, nullptr);
    }

    std::queue<TreeNode*> queue;
    queue.push(root);
    int d = 0;
    while (queue.size()) {
      d++;
      auto n = queue.size();
      for (size_t i = 0; i < n; ++i) {
        auto top = queue.front();
        queue.pop();
        if (d + 1 == depth) {
          top->left = new TreeNode(val, top->left, nullptr);
          top->right = new TreeNode(val, nullptr, top->right);
        }
        if (d + 1 != depth) {
          if (top->left) queue.push(top->left);
          if (top->right) queue.push(top->right);
        }
      }
      if (d + 1 == depth) return root;
    }

    return nullptr;
  }
};
