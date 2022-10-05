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
  // should use Euler Traversal, but IDK
  // This approach is LCA + Backtracking
  // Another genius approach is just building two paths, remove common prefix.
  string getDirections(TreeNode* root, int startValue, int destValue) {
    auto common = lca(root, startValue, destValue);
    std::vector<TreeNode*> src_stack{common};
    std::vector<TreeNode*> dst_stack{common};
    bt(common, src_stack, startValue);
    bt(common, dst_stack, destValue);

    std::string str(src_stack.size() - 1, 'U');

    for (size_t i = 0; i < dst_stack.size() - 1; ++i) {
      auto curr = dst_stack[i];
      auto next = dst_stack[i + 1];
      str.push_back(curr->left == next ? 'L' : 'R');
    }

    return str;
  }

  bool bt(TreeNode* root, std::vector<TreeNode*>& stack, int target) {
    if (root == nullptr) return false;
    if (root->val == target) return true;

    stack.push_back(root->left);
    auto left = bt(root->left, stack, target);
    if (!left) stack.pop_back();
    stack.push_back(root->right);
    auto right = bt(root->right, stack, target);
    if (!right) stack.pop_back();

    return left | right;
  }

  TreeNode* lca(TreeNode* root, int src, int dst) {
    if (root == nullptr) return root;
    if (root->val == src || root->val == dst) return root;

    auto left = lca(root->left, src, dst);
    auto right = lca(root->right, src, dst);
    if (left && right) return root;

    return left ? left : right;
  }
};
