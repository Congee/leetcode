#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int longestOnes(vector<int>& nums, int k) {
    int n = nums.size();
    int max_len = k;

    std::array<int, 2> counts = {};
    for (int lo = 0, hi = 0; hi < n; ++hi) {
      counts[nums[hi]]++;

      while (counts[0] > k) counts[nums[lo++]]--;

      max_len = std::max(max_len, hi - lo + 1);
    }

    return max_len;
  }
};
