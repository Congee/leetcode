#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  bool isOneEditDistance(string& s, string& t) {
    return two_pointers(s, t, 1) == 1;
    return edit_distance(s, t) == 1;
  }

  bool two_pointers(string_view s, string_view t, int k) {
    if (k < 0) return false;
    if (s.empty()) return t.size() == k;
    if (t.empty()) return s.size() == k;

    int n = s.size(), m = t.size(), i = 0, j = 0;
    while (i < n && j < m) {
      bool eq = s[i] == t[j];

      if (eq) {
        i++;
        j++;
      } else {
        return two_pointers(s.substr(i), t.substr(j + 1), k - 1) ||
               two_pointers(s.substr(i + 1), t.substr(j), k - 1) ||
               two_pointers(s.substr(i + 1), t.substr(j + 1), k - 1);
      }
    }

    return (n - i == 0 && m - j == k) || (n - i == k && m - j == 0);
  }

  bool edit_distance(string& s, string& t) {
    int n = s.size(), m = t.size();
    if (std::abs(n - m) > 1) return false;

    // s = "ab", t = "a"
    //     j 0
    // i   ? a
    // 0 ? 0 1
    // 1 b 1 1
    // 2 a 2 1  -> dp[n][m] = 1
    std::vector<std::vector<long>> dp(n + 1, std::vector<long>(m + 1));
    for (int i = 0; i <= n; ++i) dp[i][0] = i;
    for (int i = 0; i <= m; ++i) dp[0][i] = i;

    // dp[i][j] = max(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1])
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j) {
        if (s[i - 1] == t[j - 1])
          dp[i][j] = dp[i - 1][j - 1];
        else
          dp[i][j] = std::min({
            dp[i - 1][j - 1] + 1,
            dp[i - 1][j] + 1,
            dp[i][j - 1] + 1,
          });
      }
    }

    return dp[n][m];
  }
};
