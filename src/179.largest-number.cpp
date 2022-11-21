#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  string largestNumber(vector<int>& nums) {
    // 1. find the max len
    // 2. padding 0s to end
    // 3. sort by desc

    std::sort(nums.begin(), nums.end(), [&](const auto& lhs, const auto& rhs) {
      // 10 1 -> 10 10
      // 100 2 -> 100 200
      // 314, 3 -> 3 314
      // 334, 3 -> 334 3
      auto lr = std::stol(std::to_string(lhs) + std::to_string(rhs));
      auto rl = std::stol(std::to_string(rhs) + std::to_string(lhs));
      return lr > rl;
    });

    std::string str;
    for (auto&& num : nums) str += std::to_string(num);

    if (str[0] == '0') return "0";

    return str;  // case: [0, 0]
  }
};

#if 0
[10,2]
[3,30,34,5,9]
[0,0]
[999999998,999999997,999999999]
#endif
