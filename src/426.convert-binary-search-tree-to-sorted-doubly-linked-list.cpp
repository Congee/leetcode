#ifdef __LOCAL__
#include <leetcode.h>

// Definition for a Node.
class Node {
 public:
  int val;
  Node* left;
  Node* right;

  Node() {}

  Node(int _val) {
    val = _val;
    left = NULL;
    right = NULL;
  }

  Node(int _val, Node* _left, Node* _right) {
    val = _val;
    left = _left;
    right = _right;
  }
};
#endif

class Solution {
 public:
  Node* treeToDoublyList(Node* curr) {
    // sorted means inorder traversal
    if (curr == nullptr) return nullptr;
    Node dummy;
    auto head = &dummy;
    std::stack<Node*> stack;

    while (curr || stack.size()) {
      while (curr) {
        stack.push(curr);
        curr = curr->left;
      }

      curr = stack.top();
      stack.top()->left = head;
      head->right = stack.top();
      head = head->right;

      stack.pop();

      curr = curr->right;
    }

    head->right = dummy.right;
    dummy.right->left = head;
    return dummy.right;
  }
};
