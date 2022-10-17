#ifdef __LOCAL__
#include <leetcode.h>
#endif

using Pair = std::pair<int, int>;
const Pair dirs[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

class Solution {
  vector<vector<int>> grid;
  int m;
  int n;
  std::vector<int> seen;
  int obstacle_cnt;

  inline bool within(int row, int col) {
    return row >= 0 && col >= 0 && row < m && col < n;
  }

 public:
  int uniquePathsIII(vector<vector<int>>& __grid) {
    grid = std::move(__grid);
    m = grid.size();
    n = grid[0].size();
    seen.assign(m * n, 0);

    Pair start;
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        if (grid[r][c] == 1) {
          start = {r, c};
          seen[r * n + c] = 1;
        }
        obstacle_cnt += grid[r][c] == -1;
      }
    }

    return backtrack(start.first, start.second, 1);
  }

  // simple case
  // 1 0 0
  // 0 0 2
  // Time O(3^n)
  int backtrack(int row, int col, int seen_cnt) {
    if (grid[row][col] == 2 && seen_cnt == m * n - obstacle_cnt) return 1;

    int cnt = 0;
    for (auto&& [dr, dc] : dirs) {
      auto r = row + dr;
      auto c = col + dc;
      const auto nb = r * n + c;
      if (!within(r, c)) continue;
      if (seen[nb]) continue;
      if (grid[r][c] == -1) continue;

      seen[nb] = true;
      seen_cnt++;
      cnt += backtrack(r, c, seen_cnt);
      seen[nb] = false;
      seen_cnt--;
    }

    return cnt;
  }
};
