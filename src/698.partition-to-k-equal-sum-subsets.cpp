#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  int n, total, mean, seen, goal, k;
  std::vector<int> nums;
  std::vector<int8_t> memo;  // 0 -> false, 1 -> true, -1 -> unset

 public:
  bool canPartitionKSubsets(vector<int>& __nums, int __k) {
    nums = std::move(__nums);
    total = std::accumulate(nums.begin(), nums.end(), 0);
    n = nums.size(), mean = total / __k, seen = 0, goal = (1 << n) - 1, k = __k;
    if (total % k) return false;
    for (int num : nums)
      if (num > mean) return false;

    return dp_backtrack();
    return backtrack();
  }

  // dp + backtrack does not necessarily result int faster runtime as it has to
  // traverse all subproblems
  bool dp_backtrack() {
    std::vector<int> dp(1 << n, -1);  // subset-sum where -1 means unset
    dp[0] = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
      if (dp[mask] == -1) continue;  // wasn't reached to mask previously

      for (int i = 0; i < n; ++i)
        if ((mask & (1 << i)) == 0 && dp[mask] + nums[i] <= mean)
          dp[mask | (1 << i)] = (dp[mask] + nums[i]) % mean;

      if (dp[(1 << n) - 1] == 0) return true;
    }

    return dp[(1 << n) - 1] == 0;
  }

  bool backtrack() {
    // some repeated calculation can be avoid, say
    // 12 34  -> false
    // 13 24 shall also fail
    // we record these masks
    memo.resize(1 << n, -1);  // 1 << n ~= 64k * 4byte

    std::sort(nums.begin(), nums.end(), std::greater<>());

    // O(k⋅2^N)
    return dfs(0, 0, 0);
  }

  bool dfs(int start, int count, int sum) {
    if (count == k) return seen == goal;
    if (memo[seen] != -1) return memo[seen];

    for (int i = start; i < n; ++i) {
      if (seen & (1 << i)) continue;
      if (sum + nums[i] > mean) continue;

      sum += nums[i];
      seen |= 1 << i;

      if (sum < mean) {
        if (dfs(i + 1, count, sum)) return true;
      } else if (dfs(0, count + 1, 0))
        return true;

      seen ^= 1 << i;
      sum -= nums[i];
    }

    return memo[seen] = false;
  }
};
