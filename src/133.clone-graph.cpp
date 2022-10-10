#ifdef __LOCAL__
#include <leetcode.h>
// Definition for a Node.
class Node {
 public:
  int val;
  vector<Node *> neighbors;
  Node() {
    val = 0;
    neighbors = vector<Node *>();
  }
  Node(int _val) {
    val = _val;
    neighbors = vector<Node *>();
  }
  Node(int _val, vector<Node *> _neighbors) {
    val = _val;
    neighbors = _neighbors;
  }
};
#endif

class Solution {
 public:
  Node *cloneGraph(Node *node) {
    if (node == nullptr) return node;
    return dfs_iter(node);

    std::unordered_map<Node *, Node *> visited;
    return dfs_recurse(node, visited);
  }

  Node *dfs_iter(Node *node) {
    // [[2,4],[1,3],[2,4],[1,3]]
    //  1     2     3     4

    // 1  2
    // 4  3

    //                 theirs ours
    std::unordered_map<Node *, Node *> visited;
    std::stack<std::pair<Node *, Node *>> stack;

    auto theirs = node;
    auto ours = new Node(node->val);
    stack.push({theirs, ours});
    visited[theirs] = ours;

    while (!stack.empty()) {
      auto [theirs, ours] = stack.top();
      stack.pop();

      for (auto nb : theirs->neighbors) {
        // do not new() always
        // we have to push a node allocated before where applicable
        if (visited.count(nb)) {
          ours->neighbors.push_back(visited[nb]);
        } else {
          auto clone = new Node(nb->val);
          ours->neighbors.push_back(clone);
          stack.push({nb, clone});
          visited[nb] = clone;
        }
      }
    }
    return ours;
  }

  Node *dfs_recurse(Node *node, std::unordered_map<Node *, Node *> &visited) {
    if (visited.find(node) != visited.end()) return visited[node];

    visited[node] = new Node(node->val);

    for (auto x : node->neighbors) {
      visited[node]->neighbors.push_back(dfs_recurse(x, visited));
    }
    return visited[node];
  }
};
