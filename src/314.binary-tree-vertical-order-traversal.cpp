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
  vector<vector<int>> verticalOrder(TreeNode* root) {
    if (root == nullptr) return {};
    // maintain and record the index for each node
    // both bfs and dfs work

    int min_pos = INT_MAX, max_pos = INT_MIN;
    std::unordered_map<int, std::vector<int>> map;
    std::queue<std::pair<TreeNode*, int>> queue({{root, 0}});  // <node, pos>
    while (queue.size()) {
      auto [curr, pos] = queue.front();
      queue.pop();
      map[pos].push_back(curr->val);
      min_pos = std::min(min_pos, pos);
      max_pos = std::max(max_pos, pos);

      if (curr->left) queue.push({curr->left, pos - 1});
      if (curr->right) queue.push({curr->right, pos + 1});
    }

    std::vector<std::vector<int>> result;
    for (int i = min_pos; i <= max_pos; ++i) {
      auto it = map.find(i);
      if (it != map.end()) result.push_back(it->second);
    }

    return result;
  }
};
