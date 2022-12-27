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
  int max_diameter = 0;

 public:
  int diameterOfBinaryTree(TreeNode* root) {
    height_of(root);
    return max_diameter;
  }

  int height_of(TreeNode* root) {  // returns max depth
    if (root == nullptr) return 0;

    auto left_height = root->left ? height_of(root->left) + 1 : 0;
    auto right_height = root->right ? height_of(root->right) + 1 : 0;
    max_diameter = std::max(max_diameter, left_height + right_height);
    return std::max(left_height, right_height);
  }
};
