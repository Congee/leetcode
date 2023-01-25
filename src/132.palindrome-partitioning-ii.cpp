#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  std::vector<std::vector<int8_t>> memo;

 public:
  int minCut(string_view s) {
    return manacher(s);
    return smart_dp(s);
  }

  int manacher(string_view s) {
    // expand from mid
    //   noon
    //   <^^>
    //
    // madam
    //  <^>
    // dp[end] = min(dp[start -1] + 1, cuts calculated so far)
    int n = s.size();
    std::vector<int> dp(n);
    std::iota(dp.begin(), dp.end(), 0);

    auto expand = [&](int start, int end) {
      for (; start >= 0 && end < n && s[start] == s[end]; --start, ++end) {
        dp[end] = std::min(dp[end], start == 0 ? 0 : dp[start - 1] + 1);
      }
    };
    for (int mid = 0; mid < n; ++mid) {
      expand(mid, mid);
      expand(mid - 1, mid);
    }

    return dp[n - 1];
  }

  int smart_dp(string_view s) {
    // in the naive_dp solution the direction of i, and j are
    // |____ i ....
    // |_____j -> ....  where j starts from i
    // actually, starting j from 0 to i rsults in easier memo[] build up
    // e.g.,
    // "babba"
    //    **
    //   ****
    //
    // At this time, we store mininum number of cuts instead of palindromes

    int n = s.size();
    memo.resize(n, std::vector<int8_t>(n));

    std::vector<long> dp(n + 1);
    std::iota(dp.begin(), dp.end(), -1);

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j <= i; ++j) {
        memo[i][j] = s[i] == s[j] && (j - i <= 2 || memo[i + 1][j - 1]);
        if (memo[i][j])
          dp[j] = i == 0 ? 0 : std::min(dp[j], dp[i - 1] + 1);
        else
          dp[j] = dp[j];
      }
    }

    return dp[0];
  }

  int naive_dp(string_view s) {
    int n = s.size();
    memo.resize(n, std::vector<int8_t>(n));

    std::vector<long> dp(n + 1);
    for (int i = 0; i < n; ++i) dp[i] = n - i;
    auto prev = dp;
    // recurrence relation
    // state : min number of palindromes @ j
    //  i
    //  j
    //  palindrome start 0 / end 1
    // |_|__|__|...
    // |_|_____|...
    // |___|___|...
    // [0, i - 1] are all palindromes, no matter how many
    // min(dp[])
    // dp[i][j] = min(dp[i][j], dp[i - 1][j]) if (dp[i - 1][j] is true and
    // better)
    //            (dp[i][j - 1] + 1) if [i, j] is palindrome
    for (int i = n - 1; i >= 0; --i) {
      for (int j = i; j >= 0; --j) {
        bool ends = memo[j][i];
        if (ends) {
          dp[j] = std::min(dp[i + 1] + 1, prev[j]);
        } else {
          dp[j] = prev[j];
        }
      }

      prev = dp;
    }

    return dp[0] - 1;
  }

  // case "abbab" traversing backwards
  bool check(string_view s, int i, int j) {
    return memo[i][j] = s[i] == s[j] &&
                        ((j - i <= 2) ||
                         (memo[i + 1][j - 1] == -1 ? check(s, i + 1, j - 1)
                                                   : memo[i + 1][j - 1]));
  };
};
