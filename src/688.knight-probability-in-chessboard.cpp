#ifdef __LOCAL__
#include <leetcode.h>
#endif

using Pair = std::pair<int, int>;
const Pair dirs[] = {
  {1, 2},
  {2, 1},
  {2, -1},
  {1, -2},
  {-1, -2},
  {-2, -1},
  {-2, 1},
  {-1, 2},
};

class Solution {
 public:
  double knightProbability(int n, int k, int row, int column) {
    // dp[k][x][y] = sum(dp[k - 1][x?][y?] * 0.125 if possible)
    // where x? Y? mean every prev direction

    std::vector<std::vector<std::vector<double>>> dp(
      k + 1,
      std::vector<std::vector<double>>(n + 1, std::vector<double>(n + 1, 0))
    );
    dp[0][row][column] = 1;

    const auto is_valid = [&](int x, int y) {
      return x >= 0 && x < n && y >= 0 && y < n;
    };

    for (int i = 1; i < k + 1; ++i) {
      for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
          for (auto&& [dx, dy] : dirs) {
            if (is_valid(x - dx, y - dy))
              dp[i][x][y] += dp[i - 1][x - dx][y - dy] * 0.125;
          }
        }
      }
    }

    double sum = 0;
    for (int x = 0; x < n; ++x) {
      sum += std::accumulate(dp[k][x].begin(), dp[k][x].end(), 0.0);
    }
    return sum;
  }
};
