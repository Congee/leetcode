#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  bool checkSubarraySum(vector<int>& nums, int k) {
    return cache_remainder(nums, k);
    return naive(nums, k);
  }

  bool cache_remainder(vector<int>& nums, int k) {
    // e.g., say k = 7
    // 15 % 7 = 1
    // 8 % 7 = 1
    // 15 - 8 is good
    int n = nums.size(), psum = 0;
    std::unordered_map<int, int> map({{0, -1}});  // <psum, idx>
    for (int i = 0; i < n; ++i) {
      psum = (psum + nums[i]) % k;
      auto it = map.find(psum);
      if (it != map.end() && i - it->second >= 2) return true;

      map.emplace(psum, i);
    }

    return false;
  }

  bool naive(vector<int>& nums, int k) {
    //         ---
    //        /
    //       /
    //     --
    //    /
    //   /
    // -
    //
    // |___|   |____|
    //  k^1      k^2

    int n = nums.size(), psum = 0;
    std::unordered_map<int, int> map({{0, 0}});  // <psum>
    for (int i = 0; i <= n; ++i) {
      int lo = 0, hi = psum, curr = psum;
      while (lo <= curr && curr <= hi) {
        auto it = map.find(curr);
        if (it != map.end() && i - it->second >= 2) return true;
        curr -= k;
      }

      if (i != n) {
        psum += nums[i];
        map.emplace(psum, i + 1);
      }

      // [0] 1
      // [1,100000] 1
      // actually any non-curated k (small prime number) could quickly
      // converges to a result if there is one
      if (psum > k && psum % k == 0) return true;
    }

    return false;
  }
};
