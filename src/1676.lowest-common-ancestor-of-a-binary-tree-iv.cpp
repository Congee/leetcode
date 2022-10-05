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
  std::unordered_set<TreeNode *> set;

 public:
  // Apply recursively. Get the node which is an ancestor of another two nodes
  // which are ancestors of ...
  TreeNode *lowestCommonAncestor(TreeNode *root, vector<TreeNode *> &nodes) {
    set.insert(nodes.begin(), nodes.end());
    return lca(root);
  }

  TreeNode *lca(TreeNode *root) {
    if (root == nullptr) return nullptr;
    if (set.count(root)) return root;

    auto left = lca(root->left);
    auto right = lca(root->right);

    if (left && right) return root;

    return left ? left : right;
  }
};

class TLE : Solution {
  std::vector<TreeNode *> ancestors;
  bool push;

 public:
  TreeNode *lowestCommonAncestor(TreeNode *root, vector<TreeNode *> &nodes) {
    push = true;
    has_descendant(root, nodes[0]);
    std::reverse(ancestors.begin(), ancestors.end());
    push = false;

    for (size_t i = 1; i < nodes.size(); ++i) {
      while (!has_descendant(ancestors.back(), nodes[i])) ancestors.pop_back();
    }

    return ancestors.back();
  }

  bool has_descendant(TreeNode *root, TreeNode *target) {
    if (root == nullptr) return false;
    // clang-format off
    bool has = root == target
            || has_descendant(root->left, target)
            || has_descendant(root->right, target);
    // clang-format on
    if (has && push) ancestors.push_back(root);
    return has;
  }
};
