#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int subarraysWithKDistinct(vector<int>& nums, size_t k) {
    return at_most(nums, k) - at_most(nums, k - 1);
  }

  int at_most(vector<int>& nums, size_t k) {
    if (k < 0) return 0;

    std::unordered_map<int, int> map;
    int n = nums.size(), count = 0;
    for (int lo = 0, hi = 0; hi < n; ++hi) {
      map[nums[hi]]++;

      while (map.size() > k) {
        if (--map[nums[lo]] == 0) map.erase(nums[lo]);
        lo++;
      }

      count += hi - lo + 1;
    }

    return count;
  }

  int naive(vector<int>& nums, size_t k) {
    // [1,2,3,3]
    // -> 2
    //
    // [1,1,2,1, 2 ,3,3,3,4]
    //
    // [1,2,2,1,3]
    // 2
    std::unordered_map<int, std::deque<int>> map;  // <num, [idx]>
    int n = nums.size();
    int count = 0;
    for (int lo = 0, hi = 0; hi < n; ++hi) {
      auto curr = nums[hi];
      map[curr].push_back(hi);

      if (map.size() < k) continue;

      while (map.size() > k) {
        auto dq = map[lo];
        dq.pop_front();
        if (dq.empty()) map.erase(lo);
        lo++;
      }

      // now map.size() == k
      int min_last_idx = INT_MAX;
      for (auto&& [k, q] : map) min_last_idx = std::min(min_last_idx, q.back());

      count += min_last_idx - lo + 1;
    }

    return count;
  }
};
