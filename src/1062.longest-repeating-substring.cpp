#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int longestRepeatingSubstring(const string_view& s) {
    auto n = s.size();
    int p = 31;
    int m = 1e9 + 7;

    std::vector<long> hashes(n + 1);
    std::vector<long> pows(n);
    pows[0] = 1;
    hashes[0] = 0;
    for (size_t i = 1; i < n; ++i)
      pows[i] = pows[i - 1] * p % m;

    for (size_t i = 0; i < n; ++i)
      hashes[i + 1] = (hashes[i] + (s[i] - 'a' + 1) * pows[i]) % m;
    
    // Iterating from longer to shorter. Return on first found
    std::unordered_set<long> seen;
    for (size_t len = s.size() - 1; len > 0; --len) {
      for (size_t i = 0; i + len <= s.size(); ++i) {
        //  01234
        // "abab"
        // "ab"
        auto hash = (hashes[i + len] + m - hashes[i]) % m;
        hash = (hash * pows[n - i - 1]) % m;
        if (seen.count(hash)) return len;
        seen.insert(hash);
      }
      seen.clear();
    }

    return 0;
  }
};
