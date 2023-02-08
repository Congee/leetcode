#ifdef __LOCAL__
#include <leetcode.h>
// Definition for a Node.
class Node {
 public:
  int val;
  Node* next;
  Node* random;

  Node(int _val) {
    val = _val;
    next = NULL;
    random = NULL;
  }
};
#endif

class Solution {
 public:
  Node* copyRandomList(Node* head) {
    // another smart idea is interleave each cloned node after the original node
    // then we can just call clone->random = curr->random->next
    // then extract cloned nodes from the interleaved.
    // This approach mutates the input.

    return iter_on_space(head);
    return graph_cycle(head);
    return space(head);
  }

  Node* iter_on_space(Node* head) {
    if (head == nullptr) return nullptr;

    auto curr = head;
    auto clone = new Node(head->val);
    std::unordered_map<Node*, Node*> map{{head, clone}};

    auto get = [&](Node* node) -> Node* {
      if (node == nullptr) return nullptr;

      auto it = map.find(node);
      if (it != map.end()) return it->second;

      return map[node] = new Node(node->val);
    };

    while (curr) {
      clone->next = get(curr->next);
      clone->random = get(curr->random);

      clone = clone->next;
      curr = curr->next;
    }

    return map[head];
  }

  Node* graph_cycle(Node* head) {
    // we need a relation betwen a node and its counterpart copy
    if (head == nullptr) return nullptr;

    std::unordered_map<Node*, Node*> map;
    auto clone = map.emplace(head, new Node(head->val)).first->second;
    clone->next = cycle(head->next, map);
    clone->random = cycle(head->random, map);
    return clone;
  }

  Node* cycle(Node* node, std::unordered_map<Node*, Node*>& map) {
    if (node == nullptr) return nullptr;
    auto it = map.find(node);
    if (it != map.end()) return it->second;

    auto clone = map.emplace(node, new Node(node->val)).first->second;
    clone->next = cycle(node->next, map);
    clone->random = cycle(node->random, map);

    return clone;
  }

  Node* space(Node* head) {
    // for simple cases of pointing to null or self, just do it
    // for cases of pointing to another node. we probably need some space
    // what about making random a index in a vector?
    // record map {node => index}
    // fill a vector of indices
    // copy

    if (head == nullptr) return nullptr;

    std::unordered_map<Node*, int> map;
    auto curr = head;
    int idx = 0;
    while (curr) {
      map[curr] = idx;
      idx++;
      curr = curr->next;
    }
    const int n = idx;

    std::vector<int> vec;  // -1 means null
    vec.reserve(n);
    curr = head;
    while (curr) {
      vec.push_back(curr->random ? map[curr->random] : -1);
      curr = curr->next;
    }

    std::vector<Node*> nodes;
    nodes.reserve(n);

    curr = head;
    while (curr) {
      nodes.push_back(new Node(curr->val));
      curr = curr->next;
    }

    for (int i = 0; i < n; ++i) {
      if (i != n - 1) nodes[i]->next = nodes[i + 1];
      nodes[i]->random = vec[i] == -1 ? nullptr : nodes[vec[i]];
    }

    return nodes[0];
  }
};
