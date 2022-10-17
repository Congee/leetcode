#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int calculateMinimumHP(vector<vector<int>>& dungeon) {
    // intuition
    // binary search + backtrack can do it, but it's slow.
    // when trying on binary search, the path is fixed.
    // just choose that path and find the minimum HP satisfying that path?
    // that won't work with skews, -1000 then 1000
    // path 1: -100,100,0,0,0,0,-1000,1000
    // path 2: -200,200,0,0,0,0,0,    0
    // so the current opt relies on later opt

    int m = dungeon.size();
    int n = dungeon[0].size();
    auto& dp = dungeon;
    // dp[r][c] = min(dp[r][c], dp[r][c] + min(dp[r + 1][c], dp[r][c + 1]))

    for (int r = m - 1; r >= 0; --r) {
      for (int c = n - 1; c >= 0; --c) {
        if (r == m - 1 && c == n - 1)
          dp[r][c] = min(dp[r][c], 0);
        else if (r == m - 1) {
          dp[r][c] = min(dp[r][c], dp[r][c] + dp[r][c + 1]);
        } else if (c == n - 1) {
          dp[r][c] = min(dp[r][c], dp[r][c] + dp[r + 1][c]);
        } else
          dp[r][c] = min(dp[r][c], dp[r][c] + max(dp[r + 1][c], dp[r][c + 1]));
      }
    }

    return dp[0][0] > 0 ? 1 : 1 - dp[0][0];
  }
};
