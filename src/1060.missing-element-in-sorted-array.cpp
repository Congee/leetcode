#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int missingElement(vector<int>& nums, int k) {
    int n = nums.size();
    // [4,*56*,7,*8*,9,10]
    //  0,     1,    2,3
    //   7-4=3   10-7=3
    //   1-0=1   3-1=2
    // k = 1 -> 5
    // k = 2 -> 6
    // k = 3 -> 8
    // k = 4 -> 11
    //
    // [1,2,4], k = 3
    // [1,2,3], k = 1
    if (nums.back() - nums.front() - (n - 1) < k)
      return nums.back() + k - (nums.back() - nums.front() - (n - 1));

    int lo = 0, hi = n - 1;
    while (lo + 1 < hi) {
      int mid = lo + (hi - lo) / 2;
      int left_missing = nums[mid] - nums[lo] - (mid - lo);

      if (k <= left_missing) {
        hi = mid;
      } else {
        lo = mid;
        k -= left_missing;
      }
    }

    return nums[lo] + k;
  }
};
