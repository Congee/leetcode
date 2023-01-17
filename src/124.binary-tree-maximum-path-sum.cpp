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
  int max = INT_MIN;

 public:
  int maxPathSum(TreeNode* root) {
    // this is not really DP, it's just divide-and-conquer
    // dp[curr] = max(dp[left], dp[right], dp[left] + dp[right])
    // max = std::max(max, dp[curr]);
    dfs(root);
    return max;
  }

  int dfs(TreeNode* root) {
    if (root == nullptr) return 0;

    int curr = root->val;
    int left = root->left ? dfs(root->left) : 0;
    int right = root->right ? dfs(root->right) : 0;
    max = std::max({max, left + curr, right + curr, left + right + curr, curr});
    return std::max({left + curr, right + curr, curr});
  }
};
