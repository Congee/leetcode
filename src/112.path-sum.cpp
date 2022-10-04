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
  bool has_path = false;

 public:
  bool hasPathSum(TreeNode* root, int targetSum) {
    if (root == nullptr) return false;
    dfs(root, 0, targetSum);
    return has_path;
  }

  inline bool is_leaf(TreeNode* node) {
    return node && !node->left && !node->right;
  }

  void dfs(TreeNode* root, int sum, int target) {
    if (has_path) return;

    sum += root->val;
    if (is_leaf(root) && sum == target) {
      has_path = true;
      return;
    }

    if (root->left) dfs(root->left, sum, target);
    if (root->right) dfs(root->right, sum, target);
  }
};
