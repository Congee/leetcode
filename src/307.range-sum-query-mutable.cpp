#ifdef __LOCAL__
#include <leetcode.h>
#endif

struct Node {
  int lo, hi, sum;
  Node *left, *right;
  Node(int __lo, int __hi) : lo(__lo), hi(__hi) {}
};

struct SegmentTree {
  std::vector<int> nums;
  Node *root;

 public:
  SegmentTree(const std::vector<int> &__nums)
    : nums(std::move(__nums)), root(build(0, nums.size() - 1)) {}

  Node *build(int lo, int hi) {
    if (lo > hi) return nullptr;

    auto node = new Node(lo, hi);
    if (lo == hi)
      node->sum = nums[lo];
    else {
      int mid = lo + (hi - lo) / 2;
      node->left = build(lo, mid);
      node->right = build(mid + 1, hi);
      node->sum = node->left->sum + node->right->sum;
    }
    return node;
  }

  void update(Node *node, int i, int val) {
    if (node->left == node->right) {
      node->sum = val;
      return;
    }

    int mid = node->lo + (node->hi - node->lo) / 2;
    if (i <= mid)
      update(node->left, i, val);
    else
      update(node->right, i, val);
    node->sum = node->left->sum + node->right->sum;
  }

  int sum_range(Node *node, int lo, int hi) {
    if (lo > hi) return 0;

    if (node->lo == lo && node->hi == hi) return node->sum;
    int mid = node->lo + (node->hi - node->lo) / 2;

    if (hi <= mid)
      return sum_range(node->left, lo, hi);
    else if (lo > mid)
      return sum_range(node->right, lo, hi);
    else
      return sum_range(node->left, lo, mid) +
             sum_range(node->right, mid + 1, hi);
  }
};

class NumArray {
  SegmentTree st;

 public:
  NumArray(vector<int> &nums) : st(nums) {}

  void update(int index, int val) { st.update(st.root, index, val); }

  int sumRange(int left, int right) {
    return st.sum_range(st.root, left, right);
  }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */
