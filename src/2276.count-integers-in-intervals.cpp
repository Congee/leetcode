#ifdef __LOCAL__
#include <leetcode.h>
#endif

struct Node {
  int lo, hi, sum;
  Node *left, *right;
  Node(int __lo, int __hi, int __sum)
    : lo(__lo), hi(__hi), sum(__sum), left(nullptr), right(nullptr) {}
};

struct SegTree {
  Node *root;
  SegTree() {
    root = new Node(0, 1e9, 0);
  }

  Node *update(Node *node, int lo, int hi) {
    if (node == nullptr) return new Node(lo, hi, hi - lo + 1);

    int mid = node->lo + (node->hi - node->lo) / 2;

    node->left = update(node->left, lo, mid);
    if (lo > mid) node->right = update(node->right, mid + 1, hi);

    node->sum = node->left->sum + node->right->sum;
    return node;
  }

};

struct SegmentTree {
  Node *root;

  void update(Node *node, int lo, int hi) {
    if (lo <= node->lo && node->hi <= hi) {
      node->sum = node->hi - node->lo + 1;
      // discard previous smaller interval; memory leak
      node->left = nullptr;
      node->right = nullptr;
      return;
    }

    //                   lo        hi
    //                                 |____node_____|
    //                   lo        hi
    // |____node_____|
    //
    //
    //        lo        hi
    // |___node_____|
    //
    //        lo        hi
    //              |___node_____|

    //    [0,5]
    //  [0,2] [3,5]
    //
    // apply [1,3] -> [1,2] [3,3]
    //
    int mid = node->lo + (node->hi - node->lo) / 2;
    if (node->left == nullptr && node->right == nullptr) {
      node->left = new Node(node->lo, mid, node->sum ? mid - node->lo + 1 : 0);
      node->right = new Node(mid + 1, node->hi, node->sum ? node->hi - mid : 0);
    }

    if (lo <= mid) update(node->left, lo, hi);
    if (hi > mid) update(node->right, lo, hi);

    node->sum = node->left->sum + node->right->sum;
  }
};

class CountIntervals : SegmentTree {
 public:
  CountIntervals() { root = new Node(0, 1e9, 0); }

  void add(int left, int right) { update(root, left, right); }

  int count() { return root->sum; }
};

/**
 * Your CountIntervals object will be instantiated and called as such:
 * CountIntervals* obj = new CountIntervals();
 * obj->add(left,right);
 * int param_2 = obj->count();
 */
