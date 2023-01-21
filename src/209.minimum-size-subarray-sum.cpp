#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int minSubArrayLen(int target, vector<int>& nums) {
    int n = nums.size(), len = INT_MAX, sum = 0;
    for (int lo = 0, hi = 0; hi < n; hi++) {
      sum += nums[hi];
      while (lo <= hi && sum >= target) {
        len = std::min(len, hi - lo + 1);
        sum -= nums[lo++];
      }
    }

    return len == INT_MAX ? -1 : len;
  }
};
