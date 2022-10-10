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
  int largestBSTSubtree(TreeNode* root) {
    // the subtree is a BST
    // number of nodes in that subtree
    // there can be none
    return std::get<2>(dfs(root));
  }

  std::tuple<int, int, int> dfs(TreeNode* root) {  // <min, max, count>
    if (root == nullptr) return {INT_MAX, INT_MIN, 0};

    auto [lmin, lmax, lcnt] = dfs(root->left);
    auto [rmin, rmax, rcnt] = dfs(root->right);

    if (lmax < root->val && root->val < rmin)
      // clang-format off
      return {
        std::min(lmin, root->val),
        std::max(rmax, root->val),
        1 + lcnt + rcnt
      };
      // clang-format on

    return {INT_MIN, INT_MAX, std::max(lcnt, rcnt)};
  }
};
