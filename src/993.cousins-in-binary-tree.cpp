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
  bool isCousins(TreeNode* root, int x, int y) { return bfs(root, x, y); }

  bool bfs(TreeNode* root, int x, int y) {
    std::queue<std::pair<TreeNode*, TreeNode*>> queue({{root, nullptr}});
    int depth = -1;
    while (queue.size()) {
      depth++;
      const int size = queue.size();
      TreeNode *parent_x = nullptr, *parent_y = nullptr;
      for (int i = 0; i < size; ++i) {
        auto [curr, prev] = queue.front();
        queue.pop();

        if (curr->val == x) {
          parent_x = prev;
        } else if (curr->val == y) {
          parent_y = prev;
        }

        if (curr->left) queue.emplace(curr->left, curr);
        if (curr->right) queue.emplace(curr->right, curr);
      }
      if (parent_x || parent_y)
        return parent_x && parent_y && parent_x != parent_y;
    }

    return false;
  }

  bool by_dfs(TreeNode* root, int x, int y) {
    // find the height and parent of each node, then check for validity
    int depth_x = -1, parent_x = -1, depth_y = -1, parent_y = -1;
    dfs(root, x, depth_x, parent_x);
    dfs(root, y, depth_y, parent_y);
    return depth_x == depth_y && parent_x != parent_y;
  }

  // returns <depth, parent>
  void dfs(
    TreeNode* root,
    int target,
    int& depth_ref,
    int& parent_ref,
    int parent = -1,
    int depth = 0
  ) {
    if (root == nullptr) return;

    if (root->val == target) {
      depth_ref = depth;
      parent_ref = parent;
      return;
    }

    if (root->left)
      dfs(root->left, target, depth_ref, parent_ref, root->val, depth + 1);
    if (root->right)
      dfs(root->right, target, depth_ref, parent_ref, root->val, depth + 1);
  }
};
