#ifdef __LOCAL__
#include <leetcode.h>
#endif

// Definition for a Node.
class Node {
 public:
  int val;
  vector<Node*> children;

  Node() {}

  Node(int _val) { val = _val; }

  Node(int _val, vector<Node*> _children) {
    val = _val;
    children = _children;
  }
};

class Solution {
  int max_diameter = 0;

 public:
  int diameter(Node* root) {
    dfs(root);
    return max_diameter;
  }

  int dfs(Node* root) {
    if (root == nullptr || root->children.empty()) return 0;

    std::vector<int> edges;
    for (auto&& node : root->children) {
      if (node) edges.push_back(dfs(node) + 1);
    }
    if (edges.size() == 0) return 0;

    std::sort(edges.begin(), edges.end());

    if (edges.size() == 1) {
      max_diameter = std::max(max_diameter, edges.back() + 1);
    } else {
      max_diameter = std::max(
        max_diameter, edges.back() + 1 + *std::next(edges.rbegin()) + 1
      );
    }
    return edges.back() + 1;
  }
};
