#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int maxProduct(vector<int>& nums) {
    // beware 0 and -1

    // split into subproblems
    // max_sofar[i] from nums[i], max_sofar, min_sofar
    // min_sofar[i] from nums[i], max_sofar, min_sofar

    int n = nums.size(), best = nums[0], max = best, min = best;
    for (int i = 1; i < n; ++i) {
      if (nums[i] < 0) std::swap(max, min);

      max = std::max(max * nums[i], nums[i]);
      min = std::min(min * nums[i], nums[i]);

      best = std::max(best, max);
    }

    return best;

    return brutal(nums);
  }

  // timeout
  int brutal(vector<int>& nums) {
    int n = nums.size(), max = INT_MIN;
    for (int i = 0; i < n; ++i) {
      int prod = nums[i];
      max = std::max(max, prod);
      for (int j = i + 1; j < n; ++j) max = std::max(max, prod *= nums[j]);
    }
    return max;
  }
};
