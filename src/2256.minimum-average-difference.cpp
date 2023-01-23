#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int minimumAverageDifference(vector<int>& nums) {
    int n = nums.size(), min_diff = INT_MAX, idx = n - 1, acc = 0;
    long sum = std::accumulate(nums.begin(), nums.end(), 0);

    // 1 2 3 4 5
    for (int i = 0; i < n; ++i) {
      acc += nums[i];  // It may be faster to use a psum array
      long avgl = acc / (i + 1);
      long avgr = i == n - 1 ? 0 : (sum - acc) / (n - i - 1);
      long diff = std::abs(avgl - avgr);
      if (diff < min_diff) {
        min_diff = diff;
        idx = i;
      }
    }

    return idx;
  }
};
