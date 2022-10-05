#ifdef __LOCAL__
#include <leetcode.h>
#endif

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
  std::unordered_set<TreeNode*> pcache;
  std::unordered_set<TreeNode*> qcache;

 public:
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    auto node = lca(root, p, q);
    if (node == p)
      return lca(p, q, q) ? p : nullptr;
    else if (node == q)
      return lca(q, p, p) ? q : nullptr;
    return node;  // including nullptr
  }

  TreeNode* lca(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == nullptr) return root;
    if (root == p || root == q) return root;

    auto left = lca(root->left, p, q);
    auto right = lca(root->right, p, q);
    if (left && right) return root;
    return left == nullptr ? right : left;
  }
};

class BigSpace : Solution {
  std::unordered_set<TreeNode*> pcache;
  std::unordered_set<TreeNode*> qcache;

 public:
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!has(root, p, pcache) || !has(root, q, qcache)) return nullptr;
    return lca(root, p, q);
  }

  TreeNode* lca(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root->left && has(root->left, p, pcache) && has(root->left, q, qcache))
      return lca(root->left, p, q);
    if (root->right && has(root->right, p, pcache) && has(root->right, q, qcache))
      return lca(root->right, p, q);

    return root;
  }

  bool has(
    TreeNode* root, TreeNode* target, std::unordered_set<TreeNode*>& cache
  ) {
    if (cache.count(target)) return true;
    bool left = false;
    bool right = false;
    if (root->left && has(root->left, target, cache)) {
      left = true;
    }
    if (root->right && has(root->right, target, cache)) {
      right = true;
    }
    if (left || right) cache.insert(root);
    return left || right;
  }
};
