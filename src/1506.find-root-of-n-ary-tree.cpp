#ifdef __LOCAL__
#include <leetcode.h>

// Definition for a Node.
class Node {
 public:
  int val;
  vector<Node *> children;

  Node() {}

  Node(int _val) { val = _val; }

  Node(int _val, vector<Node *> _children) {
    val = _val;
    children = _children;
  }
};

#endif

class Solution {
  std::unordered_map<Node *, Node *> parents;

 public:
  Node *findRoot(vector<Node *> tree) {
    return xor_ptrs(tree);
    return yolo(tree);
    return indegree(tree);
  }

  Node *xor_ptrs(vector<Node *> tree) {
    long long xorsum = 0;
    for (auto node : tree) {
      xorsum ^= (long long)(void *)node;
      for (auto child : node->children) xorsum ^= (long long)(void *)child;
    }

    return (Node *)xorsum;
  }

  Node *yolo(vector<Node *> tree) {
    // build from the indegree approach
    // then it becomes finding the missing unique number by xor-ing pointers
    // That's one-pass but needs some type casting
    // we can do + -

    int sum = 0;
    for (auto node : tree) {
      sum += node->val;
      for (auto child : node->children) sum -= child->val;
    }

    for (auto node : tree)
      if (node->val == sum) return node;

    return nullptr;
  }

  Node *indegree(vector<Node *> tree) {
    // root has indegree 0
    std::unordered_set<Node *> seen;
    for (auto node : tree) {
      for (auto child : node->children) seen.insert(child);
    }

    for (auto node : tree)
      if (seen.count(node) == 0) return node;

    return nullptr;
  }

  Node *quick_find(vector<Node *> tree) {
    for (auto node : tree) {
      for (auto child : node->children) {
        parents[child] = node;
      }
    }

    return find(tree[0]);
  }

  Node *find(Node *node) {
    auto it = parents.find(node);
    if (it == parents.end()) return node;
    return find(it->second);
  }
};
