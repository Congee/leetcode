#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int splitArray(vector<int>& nums, int k) {
    int n = nums.size();
    std::vector<int> psum(n + 1);
    psum[0] = 0;
    std::inclusive_scan(nums.begin(), nums.end(), std::next(psum.begin()));

    int lo = *std::max_element(nums.begin(), nums.end());
    int hi = psum.back();
    int splits = 0;
    while (lo <= hi) {
      int mid = lo + (hi - lo) / 2;

      if (needed(psum, mid) <= k) {
        hi = mid - 1;
        splits = mid;
      } else
        lo = mid + 1;
    }

    return splits;
  }

  // [1,2,4] k = 2
  int needed(vector<int>& psum, int sum) {
    int splits = 0, n = psum.size() - 1;
    for (int lo = 0, hi = 0; hi < n; ++hi) {
      if (psum[hi + 1] - psum[lo] > sum) {
        splits++;
        lo = hi;
      }
    }
    return splits + 1;
  }
};
