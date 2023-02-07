#ifdef __LOCAL__
#include <leetcode.h>
// Definition for a Node.
class Node {
 public:
  int val;
  Node* left;
  Node* right;
  Node* parent;
};
#endif

class Solution {
  Node *min, *src;
  std::unordered_set<Node*> seen;

 public:
  Node* inorderSuccessor(Node* node) {
    // case 1: has right. go right, then go as left as possible
    // case 2: go to a left parent as much as possible

    if (node->right) {
      node = node->right;
      while (node->left) node = node->left;
      return node;
    }

    while (node->parent && node->parent->right == node) node = node->parent;
    return node->parent;
  }

  Node* stupid(Node* node) {
    // if has right. that's it
    // if has a parent on right, that's it
    // if has a parent on left, recurse on that parent
    //
    // what about rightmost?
    // just loop lookup
    min = nullptr, src = node;
    successor(node);
    return min == node ? nullptr : min;
  }

  void successor(Node* node) {
    if (node == nullptr) return;
    if (!seen.emplace(node).second) return;
    if (node->val > src->val) {
      if (min == nullptr || min->val > node->val) min = node;
    }

    if (node->val <= src->val) return successor(node->parent);
    if (node->left && node->left->val > src->val) return successor(node->left);
    successor(node->right);
  }
};
