#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int minimumSplits(vector<int>& nums) {
    // [12,6,3,14,8] -> 2
    // [4,12,6,14] -> 1
    // [2,2,2] -> 3

    int n = nums.size();
    int count = 0;
    int prev_gcd = 1;

    for (int i = 0; i < n; ++i) {
      if ((prev_gcd = std::gcd(prev_gcd, nums[i])) > 1) continue;

      count++;
      prev_gcd = nums[i];
    }

    return count;
  }
};
