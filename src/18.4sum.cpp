#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  vector<vector<int>> fourSum(vector<int>& nums, int target) {
    int n = nums.size();
    std::sort(nums.begin(), nums.end());

    // [-2,-1,0,0,1,2]
    std::vector<std::vector<int>> vec;
    for (int i = 0; i < n; ++i) {
      if (i > 0 && nums[i - 1] == nums[i]) continue;
      for (int j = i + 1; j < n; ++j) {
        if (j > i + 1 && nums[j - 1] == nums[j]) continue;

        long sum = nums[i] + nums[j];
        for (auto&& tmp : two_pointers(nums, j + 1, target - sum))
          vec.push_back({nums[i], nums[j], nums[tmp[0]], nums[tmp[1]]});
      }
    }

    return vec;
  }

  vector<vector<int>> two_pointers(vector<int>& nums, int start, long target) {
    int n = nums.size();
    int lo = start, hi = n - 1;
    std::vector<std::vector<int>> vec;

    while (lo < hi) {
      int sum = nums[lo] + nums[hi];
      if (sum == target) {
        vec.push_back({lo++, hi});
        while (lo < hi && nums[lo - 1] == nums[lo]) lo++;
      } else if (sum < target)
        lo++;
      else if (sum > target)
        hi--;
    }
    return vec;
  }

  vector<int> hashset(vector<int>& nums, int start, int target) { return {}; }
};
