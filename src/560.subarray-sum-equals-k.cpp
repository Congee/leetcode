#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int subarraySum(vector<int>& nums, int k) { return by_prefixsum(nums, k); }

  int by_prefixsum(vector<int>& nums, int k) {
    // XXX: the key is how many times a psum occurs. Then, the diff distance.
    // nums = [1,1,1] k = 2
    // psum = [1,2,3]
    //
    // nums = [1,1,0,1] k = 2
    // psum = [1,2,2,3]
    std::unordered_map<int, int> cache({{0, 1}});  // <psum, psum_count>
    int psum = 0, count = 0;
    for (int num : nums) {
      psum += num;
      auto it = cache.find(psum - k);
      if (it != cache.end()) count += it->second;
      cache[psum]++;
    }

    return count;
  }

  // Does NOT work with negative numbers
  // [-1,-1,1]
  // 0
  int at_most(std::vector<int>& nums, int k) {
    if (k < 0) return 0;

    int n = nums.size(), count = 0;
    for (int lo = 0, hi = 0; hi < n; ++hi) {
      k -= nums[hi];

      // nums = [0,0,0] k = 0
      while (k < 0) k += nums[lo++];
      count += hi - lo + 1;
    }

    return count;
  }
};
