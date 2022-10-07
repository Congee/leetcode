#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  string minWindow(const std::string& s, const std::string& t) {
    size_t lo = 0, hi = 0, min_len = INT_MAX, min_lo = 0;
    int remaining = t.size();
    std::array<int, 128> hist = {};
    for (char c : t) hist[c]++;

    while (hi < s.size()) {
      // expand to right
      if (--hist[s[hi++]] >= 0) remaining--;
      while (remaining == 0) {
        if (hi - lo < min_len) {
          min_len = hi - lo;
          min_lo = lo;
        }
        // contract from left
        // aaab
        //  aab
        if (++hist[s[lo++]] > 0) remaining++;
      }
    }

    return min_len == INT_MAX ? "" : s.substr(min_lo, min_len);
  }
};
