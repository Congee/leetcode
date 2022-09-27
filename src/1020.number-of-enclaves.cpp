#ifdef __LOCAL__
#include <leetcode.h>
#endif

static const auto dirs =
  std::vector<std::pair<int, int>>{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

class Solution {
  vector<vector<int>> grid;
  vector<vector<bool>> seen;
  int m;
  int n;
  int max_area = 0;

 public:
  int numEnclaves(vector<vector<int>>& __grid) {
    // This solution is slow. Try mark all non-enclaves and count the rest
    grid = std::move(__grid);
    m = grid.size();
    n = grid[0].size();
    seen.assign(m, std::vector<bool>(n, 0));

    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        if (grid[r][c] == 1 && !seen[r][c]) dfs(r, c);
      }
    }

    return max_area;
  }

  void dfs(int row, int col) {
    for (auto&& [dr, dc] : dirs) {
      auto xr = row + dr;
      auto xc = col + dc;
      if (xr < 0 || xc < 0 || xr == m || xc == n) return;
    }
    std::stack<std::pair<int, int>> stack;
    stack.emplace(row, col);
    seen[row][col] = 1;

    int area = 0;
    bool reaches_boarder = false;
    while (stack.size()) {
      auto [r, c] = stack.top();
      stack.pop();
      area++;

      for (auto&& [dr, dc] : dirs) {
        auto xr = r + dr;
        auto xc = c + dc;
        if (xr < 0 || xc < 0 || xr == m || xc == n) {
          reaches_boarder = true;
          continue;
        };
        if (grid[xr][xc] == 0) continue;
        if (seen[xr][xc]) continue;

        stack.emplace(xr, xc);
        seen[xr][xc] = 1;
      }
    }
    if (reaches_boarder) return;

    max_area += area;
  }
};
