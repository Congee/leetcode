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
  int max = 0;

 public:
  int longestUnivaluePath(TreeNode* root) {
    dfs(root);
    return max;
  }

  int dfs(TreeNode* root) {
    if (root == nullptr) return 0;

    int left = dfs(root->left);
    int right = dfs(root->right);
    int uni_l = 0, uni_r = 0;

    if (root->left && root->val == root->left->val) uni_l = left + 1;
    if (root->right && root->val == root->right->val) uni_r = right + 1;

    max = std::max(max, uni_l + uni_r);
    return std::max(uni_l, uni_r);
  }
};
