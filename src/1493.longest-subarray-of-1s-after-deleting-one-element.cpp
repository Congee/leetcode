#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int longestSubarray(vector<int>& nums) {
    size_t max_len = 0;
    std::array<int, 2> map = {};
    for (size_t lo = 0, hi = 0; hi < nums.size(); ++hi) {
      map[nums[hi]]++;

      while (map[0] > 1) map[nums[lo++]]--;

      max_len = std::max(max_len, hi - lo);
    }

    return max_len;
  }
};
