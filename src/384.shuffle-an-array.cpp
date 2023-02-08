#ifdef __LOCAL__
#include <leetcode.h>
#endif

#include <random>

class Solution {
  const int n;
  std::vector<int> original, array;
  std::random_device rd;
  std::mt19937 rng;

 public:
  Solution(vector<int>& nums)
    : n(nums.size()), original(nums), array(nums), rng(rd()) {}

  vector<int> reset() { return array = original; }

  vector<int> shuffle() {
    // Fisher-Yates; Durstenfeld's version
    for (int i = n - 1; i >= 1; --i) {
      auto idx = std::uniform_int_distribution<>(0, i)(rng);
      std::swap(array[idx], array[i]);
    }

    return array;
  }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */
