#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int waysToSplitArray(vector<int>& nums) {
    int n = nums.size();
    std::vector<long> psum(n + 1);
    psum[0] = 0;
    for (int i = 0; i < n; ++i)
      psum[i + 1] = nums[i] + psum[i];
    // psum is not sorted. cannot use binary search

    // 0,0,0,0
    // 1,2,3,4
    int count = 0;
    for (int i = 0; i < n - 1; ++i)
      count += psum[i + 1] >= (psum.back() - psum[i + 1]);
    return count;
  }
};
