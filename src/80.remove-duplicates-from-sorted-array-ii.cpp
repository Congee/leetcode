#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int removeDuplicates(vector<int>& nums) {
    int n = nums.size(), k = 0, hi = nums.size() - 1;

    // [1,1,1,2,2,3]
    for (int i = n - 1; i >= 0;) {
      int cnt = 1, lo = i, x = i;
      while (x - 1 >= 0 && nums[x - 1] == nums[x]) {
        x--;
        cnt++;
      }

      if (cnt > 2) {
        shift(nums, cnt - 2, lo, hi);
        hi -= cnt - 2;
        k += cnt - 2;
        i -= cnt - 2;
      } else
        i -= cnt;
    }

    return n - k;
  }

  void shift(std::vector<int>& nums, int delta, int lo, int hi) {
    for (int i = lo; i <= hi; ++i) nums[i - delta] = nums[i];
  }
};
