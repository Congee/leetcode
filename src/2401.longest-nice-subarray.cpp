#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int longestNiceSubarray(vector<int>& nums) {
    int n = nums.size();
    // 10000000
    // 01000010
    // 00001001
    //
    // 00000011

    int max_len = 1;
    int acc = 0;

    for (int lo = 0, hi = 0; hi < n; ++hi) {
      auto curr = nums[hi];

      while (curr & acc) acc &= ~nums[lo++];  // acc ^= nums[lo++]

      acc |= curr;

      max_len = std::max(max_len, hi - lo + 1);
    }

    return max_len;
  }
};
