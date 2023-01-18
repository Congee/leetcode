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
  std::vector<int> vec;

 public:
  vector<int> rightSideView(TreeNode* root) {
    if (root == nullptr) return {};
    dfs(root, 0);
    return vec;
    return bfs(root);
  }

  void dfs(TreeNode* root, size_t level) {
    if (level == vec.size()) vec.push_back(root->val);
    if (root->right) dfs(root->right, level + 1);
    if (root->left) dfs(root->left, level + 1);
  }

  vector<int> bfs(TreeNode* root) {
    // bfs
    std::queue<TreeNode*> queue({root});
    std::vector<int> vec;
    while (queue.size()) {
      const int size = queue.size();
      for (int i = 0; i < size; i++) {
        auto curr = queue.front();
        queue.pop();
        if (i == size - 1) vec.push_back(curr->val);

        if (curr->left) queue.push(curr->left);
        if (curr->right) queue.push(curr->right);
      }
    }

    return vec;
  }
};
