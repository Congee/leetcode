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
  int sum = 0;

 public:
  int sumNumbers(TreeNode* root) {
    dfs(root, 0);
    return sum;
  }

  void dfs(TreeNode* root, int prev) {
    if (root == nullptr) return;

    int sofar = prev * 10 + root->val;
    if (!root->left && !root->right) sum += sofar;

    dfs(root->left, sofar);
    dfs(root->right, sofar);
  }
};
