#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int deleteString(const string_view &s) {
    int n = s.size();
    int p = 31;
    int m = 1e9 + 7;
    std::vector<long> pows(n);
    std::vector<long> hs(n + 1);
    pows[0] = 1;
    for (int i = 1; i < n; ++i)
      pows[i] = pows[i - 1] * p % m;

    hs[0] = 0;
    for (int i = 0; i < n; ++i)
      hs[i + 1] = (hs[i] + pows[i] * (s[i] - '`') % m) % m;

    // aaabaab
    // -aa-
    // aaa-aa-
    auto cmp = [&](int i, int len) {
      auto foo = (hs[i + len] - hs[i] + m) % m;
      auto bar = (hs[i + len + len] - hs[i + len] + m) % m;
      return pows[len] * foo % m == bar && s.substr(i, len) == s.substr(i + len, len);
    };

    std::vector<int> dp(n + 1, -1);
    dp.back() = 0;
    for (int i = n - 1; i >= 0; --i) {
      for (int len = (n - i) / 2; len >= 1; --len) {
        if (cmp(i, len)) {
          dp[i] = std::max(dp[i], 1 + dp[i + len]);
        }
      }

      if (dp[i] == -1) dp[i] = 1;
    }

    return dp[0];
  }
};
