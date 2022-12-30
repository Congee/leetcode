#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  std::vector<std::vector<int>> memo;

 public:
  bool canPartition(vector<int>& nums) {
    return topdown(nums);
    return bottomup(nums);
  }

  bool topdown(vector<int>& nums) {
    int n = nums.size(), sum = std::accumulate(nums.begin(), nums.end(), 0);
    if (sum & 1) return false;
    int target = sum / 2;
    memo = std::vector<std::vector<int>>(n, std::vector<int>(target + 1, -1));

    // dp(i, rem) = dp(i + 1, rem + nums[i + 1]) == target
    //           || dp(i + 1, rem)
    return dfs(nums, 0, target);
  }

  bool dfs(std::vector<int>& nums, size_t idx, int sum) {
    if (idx == nums.size()) return false;
    if (sum < 0) return false;
    if (sum == 0) return true;
    if (memo[idx][sum] != -1) return memo[idx][sum];

    return memo[idx][sum] = dfs(nums, idx + 1, sum - nums[idx]) ||
                            dfs(nums, idx + 1, sum);
  }

  bool bottomup(std::vector<int>& nums) {
    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    if (sum & 1) return false;
    int target = sum / 2;

    std::vector<int8_t> dp(target + 1, false);
    dp.front() = true;
    for (int num : nums)
      for (int j = target; j >= num; --j) dp[j] |= dp[j - num];

    return dp[target];
  }
};
