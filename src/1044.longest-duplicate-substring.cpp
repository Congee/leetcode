#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  /// Note that if there is a duplicate substring of length k, that means that
  /// there is a duplicate substring of length k - 1.
  ///
  /// So, binary search on rabin-karp
  ///
  string longestDupSubstring(const std::string& s) {
    int n = s.size();

    int lo = 0;
    int hi = n;
    int offset = -1;
    int len = -1;
    // tttttttfffffffffffffff
    // ______*_______________
    while (lo < hi) {
      int mid = lo + (hi - lo) / 2;
      auto idx = rabin_karp(s, mid);
      if (idx != -1) {
        offset = std::max(offset, idx);
        len = std::max(len, mid);
      }
      if (idx == -1)
        hi = mid;
      else
        lo = mid + 1;
    }

    return offset == -1 ? "" : s.substr(offset, len);
  }

  int rabin_karp(const std::string& s, size_t len) {
    auto n = s.size();
    int p = 31;
    int m = 1e9 + 7;

    long pow_rm = 1;
    for (size_t i = 1; i < len; ++i)
      pow_rm = (pow_rm * p) % m;
    // abcde
    // ab
    long roll = 0;
    for (size_t i = 0; i < len; ++i)
      roll = (roll * p + s[i]) % m;

    std::unordered_map<long, int> seen;
    seen.insert({roll, 0});
    for (size_t i = len; i < n; ++i) {
      roll = (roll + m - pow_rm * s[i - len] % m) % m;
      roll = (roll * p + s[i]) % m;

      // still could have collision
      auto it = seen.find(roll);
      int offset = i - len + 1;
      if (it != seen.end() && s.substr(it->second, len) == s.substr(offset, len))
        return offset;
      seen.insert({roll, offset});
    }

    return -1;
  }
};
