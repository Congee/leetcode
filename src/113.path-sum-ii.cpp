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
  std::vector<std::vector<int>> result;
  std::vector<int> stack;

 public:
  vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
    if (root == nullptr) return {};
    stack.push_back(root->val);
    dfs(root, root->val, targetSum);
    return result;
  }

  void dfs(TreeNode* root, int sofar, int target) {
    if (!root->left && !root->right && sofar == target) result.push_back(stack);

    if (root->left) {
      stack.push_back(root->left->val);
      dfs(root->left, sofar + root->left->val, target);
      stack.pop_back();
    }

    if (root->right) {
      stack.push_back(root->right->val);
      dfs(root->right, sofar + root->right->val, target);
      stack.pop_back();
    }
  }
};
