#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int triangleNumber(vector<int>& nums) {
    return two_pointers(nums);
    return bs(nums);
  }

  int two_pointers(vector<int>& nums) {
    std::sort(nums.begin(), nums.end());
    int count = 0, n = nums.size();

    for (int i = n - 1; i >= 2; --i) {
      for (int l = 0, r = i - 1; l < r;) {
        if (nums[l] + nums[r] > nums[i]) {
          count += r - l;
          r--;
        } else
          l++;
      }
    }

    return count;
  }

  int bs(vector<int>& nums) {
    // a + b > c
    // asking number of valid tri
    // sort and do two-pass
    // find all those valid combos
    // optimize with binary search

    // [2,2,3,4]
    // [2,2, 3,3,3,3,3,3, 4]
    // for (2, 2) count between 2 and 4

    std::sort(nums.begin(), nums.end());
    int n = nums.size(), count = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        auto hi =
          std::lower_bound(nums.begin(), nums.end(), nums[i] + nums[j]) - 1;
        auto lo = nums.begin() + j;
        int diff = hi - lo - 1;
      }
    }

    return count;
  }
};
