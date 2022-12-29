#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int lengthOfLIS(vector<int>& nums) {
    return build_sequence_bs(nums);
    return simplified_bs(nums);
    return build_sequence(nums);
    return naive_dp(nums);
  }

  int naive_dp(vector<int>& nums) {
    std::vector<int> dp(nums.size(), 1);

    // [2,4,3,7]
    int longest = 1;
    for (size_t i = 0; i < nums.size(); ++i) {
      for (int j = i - 1; j >= 0; --j) {
        if (nums[j] < nums[i]) dp[i] = std::max(dp[i], dp[j] + 1);
      }
      longest = std::max(longest, dp[i]);
    }

    return longest;
  }

  // derived from the Patience Sorting algorithm
  int build_sequence(vector<int>& nums) {
    std::vector<int> vec({nums[0]});
    for (size_t i = 1; i < nums.size(); ++i) {
      if (nums[i] > vec.back())
        vec.push_back(nums[i]);
      else {
        // [2,5,7] 6
        // [2,6,7]
        int j = 0;
        while (vec[j] <= nums[i]) ++j;
        vec[j] = nums[i];
      }
    }
    return vec.size();
  }

  int build_sequence_bs(vector<int>& nums) {
    std::vector<int> vec({nums[0]});
    for (size_t i = 1; i < nums.size(); ++i) {
      if (nums[i] > vec.back())
        vec.push_back(nums[i]);
      else
        *std::lower_bound(vec.begin(), vec.end(), nums[i]) = nums[i];
    }
    return vec.size();
  }

  int simplified_bs(vector<int>& nums) {
    std::vector<int> vec;
    for (int num : nums) {
      auto it = std::lower_bound(vec.begin(), vec.end(), num);
      if (it == vec.end())
        vec.push_back(num);
      else
        *it = num;
    }
    return vec.size();
  }
};
