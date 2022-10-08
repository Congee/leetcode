#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int numberOfSubarrays(vector<int>& nums, int k) { return fast(nums, k); }

  int fast(vector<int>& nums, int k) {
    // [1,1,1,1,1]
    // k = 2
    std::array<int, 2> map = {};
    size_t total = 0;
    size_t count = 0;
    for (size_t lo = 0, hi = 0; hi < nums.size(); ++hi) {
      ++map[nums[hi] % 2];
      if (nums[hi] & 1) count = 0;

      // 0 0 1 0 0 0 0
      // 0 0 1 0
      // _ <- same answer here
      while (map[1] == k) {
        map[nums[lo++] % 2]--;
        count++;
      }
      total += count;  // XXX: count can be used multiple times if not updated
    }

    return total;
  }

  // O(n^2)
  int slow(vector<int>& nums, int k) {
    // [1,1,1,1,1]
    // k = 2
    for (auto&& num : nums) num %= 2;

    std::array<int, 2> map = {};
    size_t count = 0;
    for (size_t lo = 0, hi = 0; hi < nums.size(); ++hi) {
      map[nums[hi] % 2]++;

      while (map[1] > k) map[nums[lo++] % 2]--;

      size_t x = lo;
      auto mmm = map;
      while (mmm[1] == k && !(nums[x] & 1)) {
        mmm[nums[x++] % 2]--;
        count++;
      }

      count += map[1] == k;
    }

    return count;
  }
};
