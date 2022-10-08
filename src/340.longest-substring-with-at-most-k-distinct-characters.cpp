#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int lengthOfLongestSubstringKDistinct(const std::string& s, int k) {
    if (k == 0) return 0;

    std::array<int, 128> map = {};
    int n = s.size(), unique_cnt = 0, max_len = 1;

    for (int lo = 0, hi = 0; hi < n; ++hi) {
      unique_cnt += ++map[s[hi]] == 1;

      while (unique_cnt > k) unique_cnt -= --map[s[lo++]] == 0;

      max_len = std::max(max_len, hi - lo + 1);
    }

    return max_len;
  }
};
