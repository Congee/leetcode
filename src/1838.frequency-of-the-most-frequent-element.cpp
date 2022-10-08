#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  long maxFrequency(vector<int>& nums, long k) {
    long n = nums.size();

    std::sort(nums.begin(), nums.end());
    std::vector<int64_t> psum(n + 1);
    psum[0] = 0;
    for (int i = 1; i < n + 1; ++i) psum[i] = psum[i - 1] + nums[i - 1];

    long max_len = 1;

    // 1,2,4
    // 0,1,3,7
    // k=1
    for (long lo = 0, hi = 0; hi < n; ++hi) {
      while (lo < hi && nums[hi] * (hi - lo) - (psum[hi] - psum[lo]) > k) lo++;

      max_len = std::max(max_len, hi - lo + 1);
    }

    return max_len;
  }
};
