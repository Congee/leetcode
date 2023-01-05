#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
    return sweep(length, updates);
    return prefix_sum(length, updates);
  }

  vector<int> prefix_sum(int length, vector<vector<int>>& updates) {
    std::vector<int> vec(length + 1, 0);

    for (auto&& update : updates) {
      int lo = update[0], hi = update[1] + 1, delta = update[2];

      vec[lo] += delta;
      vec[hi] -= delta;
    }

    for (int i = 1; i < length; ++i) vec[i] += vec[i - 1];
    vec.pop_back();
    return vec;
  }

  vector<int> sweep(int length, vector<vector<int>>& updates) {
    std::vector<int> vec(length + 1, 0);

    for (auto&& update : updates) {
      int lo = update[0], hi = update[1] + 1, delta = update[2];
      vec[lo] += delta;
      vec[hi] -= delta;
    }

    int curr = 0;
    for (int i = 0; i < length; ++i) {
      curr += vec[i];
      vec[i] = curr;
    }

    vec.pop_back();
    return vec;
  }
};
