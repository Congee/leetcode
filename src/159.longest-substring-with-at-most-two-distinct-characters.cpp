#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int lengthOfLongestSubstringTwoDistinct(const std::string& s) {
    int n = s.size();
    int max_len = 1;
    std::array<int, 128> map = {};
    int unique_cnt = 0;
    for (int lo = 0, hi = 0; hi < n; ++hi) {
      map[s[hi]]++;
      if (map[s[hi]] == 1) unique_cnt++;

      // eceba
      // eceb
      while (unique_cnt > 2) {
        map[s[lo]]--;
        if (map[s[lo]] == 0) unique_cnt--;
        lo++;
      }

      max_len = std::max(max_len, hi - lo + 1);
    }

    return max_len;
  }
};
