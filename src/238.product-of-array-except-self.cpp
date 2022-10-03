#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size();
    std::vector<int> prefix(n + 1);
    std::vector<int> suffix(n + 1);
    prefix[0] = 1;
    suffix.back() = 1;
    std::inclusive_scan(
      nums.begin(), nums.end(), std::next(prefix.begin()), std::multiplies<>()
    );
    std::inclusive_scan(
      nums.rbegin(),
      nums.rend(),
      std::next(suffix.rbegin()),
      std::multiplies<>()
    );

    std::vector<int> vec(n);
    for (int i = 0; i < n; ++i)
      vec[i] = prefix[i] * suffix[i + 1];

    return vec;
  }
};
