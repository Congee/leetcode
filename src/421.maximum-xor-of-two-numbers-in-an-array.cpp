#ifdef __LOCAL__
#include <leetcode.h>
#endif

struct Node {
  bool bit;
  int num;  // default -1
  std::array<Node *, 2> map;
  Node(bool __bit) : bit(__bit), num(-1), map({}) {}
};

class Solution {
 public:
  void insert(Node *node, int num, int size) {
    auto curr = node;
    // 1011, size = 4
    for (int i = 0; i < size; ++i) {
      bool bit = ((num >> (size - i - 1)) & 1);
      if (curr->map[bit] == nullptr) {
        curr->map[bit] = new Node(bit);
      }
      curr = curr->map[bit];
    }
    curr->num = num;
  }

  int search(Node *node, int num, int size) {
    auto curr = node;
    if (curr == nullptr) return 0;

    // greedily look for 1
    for (int i = 0; i < size; ++i) {
      // try to go the opposite bit
      bool bit = (num >> (size - i - 1)) & 1;
      bool opposite = bit & 1 ? 0 : 1;

      if (curr->map[opposite] != nullptr) {
        curr = curr->map[opposite];
      } else {
        curr = curr->map[bit];
      }
    }
    return curr->num ^ num;
  }

  size_t bit_width(int n) { return n == 0 ? 0 : std::log2(n) + 1; }

  // O(32)
  int findMaximumXOR(vector<int> &nums) {
    auto root = new Node(0);
    size_t max_width = 0;
    for (auto n : nums) {
      max_width = std::max(max_width, bit_width(n));
    }

    for (auto n : nums) insert(root, n, max_width);

    int max_xor = 0;
    for (auto n : nums) max_xor = std::max(max_xor, search(root, n, max_width));

    return max_xor;
  }
};

// [3,10,5,25,2,8]
// [14,70,53,83,49,91,36,80,92,51,66,70]
// [0,0]
