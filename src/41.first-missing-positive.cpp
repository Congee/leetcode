#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int firstMissingPositive(vector<int>& nums) {
    // [0,2,4,6,-1]
    // [2,4,6,0,-1]
    // [3,1,5,0,-1]
    return cycle_sort(nums);
    return index_as_key(nums);
  }

  int index_as_key(vector<int>& nums) {
    int n = nums.size(), min = INT_MAX;
    for (int num : nums) {
      if (num <= 0) continue;
      min = std::min(min, num);
    }

    if (min != 1) return 1;

    for (int& num : nums)
      if (num <= 0 || num > n) num = 1;

    for (int i = 0; i < n; ++i) {
      int loc = std::abs(nums[i]);
      if (loc == n) {
        if (nums[0] > 0) nums[0] *= -1;
      } else {
        if (nums[loc] > 0) nums[loc] *= -1;
      }
    }

    for (int i = 1; i < n; ++i)
      if (nums[i] > 0) return i;

    if (nums[0] > 0) return n;

    return n + 1;
  }

  int cycle_sort(vector<int>& nums) {
    int n = nums.size();
    for (int i = 0; i < n;) {
      int j = nums[i] - 1;
      if (0 <= j && j < n && nums[i] != nums[j])
        std::swap(nums[i], nums[j]);
      else
        i++;
    }

    for (int i = 0; i < n; ++i) {
      if (nums[i] != i + 1) return i + 1;
    }
    return n + 1;
  }
};
