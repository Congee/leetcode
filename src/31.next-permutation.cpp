#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  void nextPermutation(vector<int>& nums) {
    // 1 2 4 5 3  -> 4 5
    // 1 2 5 4 3
    //
    // 1 2 4 3 1  -> 2 3
    // 1 3 1 2 4
    //
    // 4 3 1 2    -> 1 2
    // 4 3 2 1

    // start backwards
    // find the largest value and the its previous one. swap them, sort the rest
    int n = nums.size(), lo = n - 1, hi = n - 2;

    while (hi >= 0 && nums[hi] >= nums[hi + 1]) hi--;

    if (hi >= 0) {
      while (nums[lo] <= nums[hi]) lo--;
      std::swap(nums[lo], nums[hi]);
    }
    std::reverse(nums.begin() + hi + 1, nums.end());
  }
};
