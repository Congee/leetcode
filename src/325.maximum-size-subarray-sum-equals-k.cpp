#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int maxSubArrayLen(vector<int>& nums, int k) {
    // the question says sum to an exact number, this gives a hint to search
    // for sum - k. So,
    // hashmap + prefix sum

    long n = nums.size(), len = 0, psum = 0;
    std::unordered_map<long, long> map({{0, 0}});
    for (int i = 0; i <= n; ++i) {
      auto it = map.find(psum - k);
      if (it != map.end()) len = std::max(len, i - it->second);

      if (i != n) {
        psum += nums[i];
        map.insert({psum, i + 1});
      }
    }

    return len;
  }
};
