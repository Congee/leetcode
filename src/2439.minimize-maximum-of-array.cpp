#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int minimizeArrayValue(vector<int>& nums) {
    int n = nums.size();
    // [1,3,5] ->
    // [3,3,3]
    //
    // [1,3,5,  7,9,11] ->
    // [3,3,3,  9,9,9] ->
    // [6,6,6,  6,6,6]
    //
    // [1,3,5,  0,9,18] ->
    // [3,3,3,  9,9,9] ->
    // [6,6,6,  6,6,6]

    long psum = 0, max = 0;
    for (int i = 0; i < n; ++i) {
      psum += nums[i];
      max = std::max(max, (psum + i) / (i + 1));  // ceil((float)psum / (i + 1))
    }

    return max;
  }
};
