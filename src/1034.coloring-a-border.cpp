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

  inline bool within(int row, int col) {
    return row >= 0 && col >= 0 && row < m && col < n;
  }

  inline bool can_color(int row, int col) {
    if (row == 0 || col == 0 || row == m - 1 || col == n - 1) return true;

    for (auto&& [dr, dc] : dirs) {
      auto xr = row + dr;
      auto xc = col + dc;
      if (grid[xr][xc] != grid[row][col]) return true;
    }

    return false;
  }

 public:
  vector<vector<int>> colorBorder(
    vector<vector<int>>& __grid, int row, int col, int color
  ) {
    grid = std::move(__grid);
    m = grid.size();
    n = grid[0].size();
    seen.assign(m, std::vector<bool>(n, 0));

    // 1 [2] 2  -> 1 3 3
    // 2  3  2     2 3 2

    // 1  1  1     2 2 2
    // 1 [1] 1  -> 2 1 2
    // 1  1  1     2 2 2

    // 1 2 1  2  1 2     1 1 1 1 1 2
    // 2 2 2 [2] 1 2  -> 1 2 1 1 1 2
    // 1 2 2  2  1 2     1 1 1 1 1 2

    std::vector<std::pair<int, int>> to_color;
    std::stack<std::pair<int, int>> stack;
    stack.emplace(row, col);
    seen[row][col] = true;
    if (can_color(row, col)) to_color.emplace_back(row, col);

    while (stack.size()) {
      auto [r, c] = stack.top();
      stack.pop();

      for (auto&& [dr, dc] : dirs) {
        auto xr = r + dr;
        auto xc = c + dc;
        if (!within(xr, xc)) continue;
        if (seen[xr][xc]) continue;

        if (grid[xr][xc] == grid[row][col]) {
          stack.emplace(xr, xc);
          if (can_color(xr, xc)) to_color.emplace_back(xr, xc);
        }
        seen[xr][xc] = true;
      }
    }

    for (auto&& [r, c] : to_color) grid[r][c] = color;

    return grid;
  }
};
