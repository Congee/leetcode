#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int countDistinct(const std::string_view& s) {
    // rolling hash O(N^2)
    // suffix array + LCP can do O(NlogN)
    auto n = s.size();
    int p = 31;
    int m = 1e9 + 7;

    std::vector<long> h(n + 1);
    std::vector<long> pows(n);
    h[0] = 0;
    pows[0] = 1;

    for (size_t i = 1; i < n; ++i)
      pows[i] = pows[i - 1] * p % m;

    for (size_t i = 0; i < n; ++i)
      h[i + 1] = h[i] + (s[i] - 'a' + 1) * pows[i] % m;

    size_t cnt = 1;
    for (size_t len = n - 1; len > 0; --len) {
      std::unordered_set<long> seen;
      // 012345
      // abcde
      // abc
      for (size_t i = 0; i < n - len + 1; ++i) {
        auto hash = (h[i + len] + m - h[i]) % m;
        hash = (hash * pows[n - i - 1]) % m;
        seen.insert(hash);
      }
      cnt += seen.size();
    }

    return cnt;
  }
};
