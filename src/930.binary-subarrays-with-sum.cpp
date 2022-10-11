#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int numSubarraysWithSum(vector<int>& nums, int goal) {
    return by_prefixsum(nums, goal);
    return at_most(nums, goal) - at_most(nums, goal - 1);
  }

  int by_prefixsum(vector<int>& nums, int k) {
    std::unordered_map<int, int> cache({{0, 1}});  // <psum, count>
    int count = 0;
    int psum = 0;
    for (int num : nums) {
      // nums = [1,0,0, 1,0,1, 0], goal = 2
      // psum = [1,1,1, 2,2,3, 3]
      // cache              @    {1: 3, 2: 2, 3: 1}
      psum += num;
      count += cache[psum - k];
      cache[psum]++;
      // below is why we update cache after updating count
      // cache({{0, 1}})
      // nums = [0,0,0]
      // psum = [0,0,0]
      // cache       @ {0: 3}
    }

    return count;
  }

  int at_most(vector<int>& nums, int k) {
    if (k < 0) return 0;

    int n = nums.size();

    // nums = [1,0,0,0,0, 1,0,1, 0,0,0,0], goal = 2
    // nums = [0,0,0,0,0], goal = 0 -> 1 + 2 + 3 + 4 + 5 == 15

    int total = 0;
    for (int lo = 0, hi = 0; hi < n; ++hi) {
      k -= nums[hi];

      // 0 0 1 0 0
      // 0 0 1 0 0 1
      while (k < 0) k += nums[lo++];

      total += hi - lo + 1;
    }

    return total;
  }
};
