#ifdef __LOCAL__
#include <leetcode.h>
#endif

const std::pair<int, int> dirs[] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

class Solution {
  vector<vector<int>> grid;
  vector<vector<int>> seen;
  int m, n;

  inline bool is_valid(int row, int col) {
    return row >= 0 && row < m && col >= 0 && col < n;
  }

 public:
  int numDistinctIslands(vector<vector<int>>& __grid) {
    // find all islands
    // map the contour close to the original point
    // calculate the hash of that contour
    grid = std::move(__grid);
    m = grid.size(), n = grid[0].size();
    seen.resize(m, std::vector<int>(n));
    std::unordered_set<size_t> hashes;
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        if (grid[r][c] == 1 && !seen[r][c]) hashes.insert(dfs(r, c));
      }
    }

    return hashes.size();
  }

  size_t dfs(int __row, int __col) {
    std::vector<std::pair<int, int>> border_cells;

    std::stack<std::pair<int, int>> stack({{__row, __col}});
    while (stack.size()) {
      auto [row, col] = stack.top();
      stack.pop();

      bool curr_is_on_border = false;
      for (auto&& [dr, dc] : dirs) {
        int r = row + dr;
        int c = col + dc;

        if (!is_valid(r, c) || grid[r][c] == 0) {
          curr_is_on_border = true;
          continue;
        }
        if (seen[r][c]) continue;

        seen[r][c] = true;
        stack.push({r, c});
      }
      if (curr_is_on_border) border_cells.push_back({row, col});
    }

    int min_row = INT_MAX, min_col = INT_MAX;
    for (auto&& [r, c] : border_cells) {
      min_row = std::min(min_row, r);
      min_col = std::min(min_col, c);
    }

    std::string str;
    for (auto&& [r, c] : border_cells) {
      str += std::to_string((r - min_row) * n + (c - min_col));
      str += '#';
    }
    if (str.size()) str.pop_back();
    return std::hash<std::string>()(str);
  }
};
