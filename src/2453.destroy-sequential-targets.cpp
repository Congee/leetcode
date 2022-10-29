#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int destroyTargets(vector<int>& nums, int space) {
    std::unordered_map<int, int> map;
    for (auto&& num : nums) map[num % space]++;
    // [1,1,3,5,7, 8,8,8,8,8,8,8,8]
    return *std::min_element(
      nums.begin(),
      nums.end(),
      [&](auto& lhs, auto& rhs) {
        auto lrem = map[lhs % space];
        auto rrem = map[rhs % space];
        return lrem == rrem ? lhs < rhs : lrem > rrem;
      }
    );
  }
};
