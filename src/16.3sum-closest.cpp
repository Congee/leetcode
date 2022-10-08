#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  vector<int> nums;
  int n;

 public:
  int threeSumClosest(vector<int>& __nums, int target) {
    nums = std::move(__nums);
    n = nums.size();
    std::sort(nums.begin(), nums.end());

    int best = nums[0] + nums[1] + nums[2];
    // 1 2 3 4
    for (int i = 0; i < n - 2; ++i) {
      auto [lo, hi] = find(i + 1, nums[i], target);
      auto curr = nums[i] + nums[lo] + nums[hi];
      if (std::abs(curr - target) < std::abs(best - target)) best = curr;
    }

    return best;
  }

  std::pair<int, int> find(int start, int curr, int target) {
    int lo = start;
    int hi = n - 1;
    int best_lo = lo;
    int best_hi = hi;
    int prev_sum = curr + nums[lo] + nums[hi];

    // -2 -1 0 1 2   --> 0
    // -1 10 11 --> 11
    while (lo < hi) {
      auto sum = curr + nums[lo] + nums[hi];
      if (std::abs(sum - target) < std::abs(prev_sum - target)) {
        best_lo = lo;
        best_hi = hi;
      }

      if (sum == target) {
        return {lo, hi};
      } else if (sum < target) {
        lo++;
      } else {
        hi--;
      }
    }

    return {best_lo, best_hi};
  }
};
