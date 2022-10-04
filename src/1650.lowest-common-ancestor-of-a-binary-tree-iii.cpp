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
  std::unordered_set<Node*> pcache;
  std::unordered_set<Node*> qcache;

 public:
  Node* lowestCommonAncestor(Node* p, Node* q) {
    return simple(p, q);

    pcache.insert(p);
    qcache.insert(q);
    return lca(p, q);
  }

  Node* simple(Node* p, Node* q) {
    Node *a = p, *b = q;
    // Slow. A hashset instead can make it faster
    while (a != b) {
      a = a == nullptr ? p : a->parent;
      b = b == nullptr ? q : b->parent;
    }
    return a;
  }

  Node* lca(Node* p, Node* q) {
    if (pcache.count(p) && qcache.count(p)) return p;
    if (pcache.count(q) && qcache.count(q)) return q;

    Node* pancestor = nullptr;
    Node* qancestor = nullptr;

    if (p->parent) {
      pcache.insert(p->parent);
      pancestor = lca(p->parent, q);
    };
    if (q->parent) {
      qcache.insert(q->parent);
      qancestor = lca(p, q->parent);
    }

    return pancestor ? pancestor : qancestor;
  }
};
