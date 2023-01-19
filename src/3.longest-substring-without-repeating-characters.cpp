#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int lengthOfLongestSubstring(string s) {
    // two pointers goind the same direction
    std::array<int, 128> map = {};
    int n = s.size(), len = 0;

    for (int lo = 0, hi = 0; hi < n; ++hi) {
      if (++map[s[hi]] > 1)
        while (map[s[hi]] > 1) map[s[lo++]]--;

      len = std::max(len, hi - lo + 1);
    }

    return len;
  }
};
