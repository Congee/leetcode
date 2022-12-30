#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int profitableSchemes(
    int members, int minProfit, vector<int>& group, vector<int>& profit
  ) {
    // dp[c][m][p] = dp[c - 1][m               ][p                ] +
    //               dp[c - 1][m - group[c - 1]][p - profit[c - 1]]
    //               if m >= group[c - 1] && p >= profit[c - 1]

    // clang-format off
    int n = group.size();
    std::vector<std::vector<std::vector<int>>> dp(
        2, std::vector<std::vector<int>>(
          members + 1, std::vector<int>(
            minProfit + 1, 0)));

    int mod = 1e9 + 7;
    dp[0][0][0] = 1;
    for (int c = 1; c < n + 1; ++c) {
      for (int m = 0; m < members + 1; ++m) {
        for (int p = 0; p < minProfit + 1; ++p) {
          int yes = dp[(c - 1) % 2][m][p];
          int prevp = std::max(p - profit[c - 1], 0);
          int no = m >= group[c - 1]
                 ? (dp[(c - 1) % 2][m - group[c - 1]][prevp])
                 : 0;

          dp[c % 2][m][p] = (yes + no % mod) % mod;
        }
      }
    }

    // clang-format on
    int sum = 0;
    for (int m = 0; m < members + 1; ++m) {
      sum = (sum + dp[n % 2][m][minProfit]) % mod;
    }
    return sum;
  }
};
