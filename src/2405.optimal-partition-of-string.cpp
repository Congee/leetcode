#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int partitionString(string& s) {
    // paraphrase
    // longest contiguous substrings of distinct character(s)
    int n = s.size(), count = 1, mask = 0;

    for (int hi = 0; hi < n; ++hi) {
      if (mask & (1 << (s[hi] - 'a'))) {
        count++;
        mask = 0;
      }
      mask |= 1 << (s[hi] - 'a');
    }

    return count;
  }
};
