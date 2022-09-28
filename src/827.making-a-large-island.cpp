#ifdef __LOCAL__
#include <leetcode.h>
#endif

static const auto dirs =
  std::vector<std::pair<int, int>>{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

// 1. Use UnionFind to find areas of all islands
// 2. Traverse all 0s, contiguous adjacent neighbors if possible
class Solution {
  vector<vector<int>> grid;
  std::vector<int> root;
  std::vector<int> rank;
  int m;
  int n;

  int find(int x) {
    if (x == root[x]) return x;
    return root[x] = find(root[x]);
  }

  void connect(int x, int y) {
    auto root_x = find(x);
    auto root_y = find(y);

    if (root_x == root_y) return;

    if (rank[root_x] < rank[root_y])
      root[root_x] = root_y;
    else if (rank[root_x] > rank[root_y])
      root[root_y] = root_x;
    else {
      root[root_y] = root_x;
      rank[root_x]++;
    }
  }

  inline bool within(int row, int col) {
    return row >= 0 && col >= 0 && row < m && col < n;
  }

 public:
  int largestIsland(vector<vector<int>>& __grid) {
    grid = std::move(__grid);
    m = grid.size();
    n = grid[0].size();

    root.resize(m * n);
    rank.assign(m * n, 1);

    bool has_zero = false;
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        root[r * n + c] = r * n + c;
        if (grid[r][c] == 0) has_zero = true;
      }
    }
    if (!has_zero) return m * n;

    // connect
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        if (grid[r][c] == 0) continue;

        for (auto&& [dr, dc] : dirs) {
          auto xr = r + dr;
          auto xc = c + dc;
          if (!within(xr, xc)) continue;
          if (grid[xr][xc] == 0) continue;

          connect(r * n + c, xr * n + xc);
        }
      }
    }

    std::unordered_map<int, int> count;
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        if (grid[r][c] == 1) count[find(r * n + c)]++;
      }
    }

    int max_area = 0;
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        if (grid[r][c] == 1) continue;

        int area = 1;
        std::unordered_set<int> seen;
        for (auto&& [dr, dc] : dirs) {
          auto xr = r + dr;
          auto xc = c + dc;
          if (!within(xr, xc)) continue;
          if (grid[xr][xc] == 0) continue;

          auto found = find(xr * n + xc);
          if (seen.count(found) == 0) {
            area += count[found];
            seen.insert(found);
          }
        }
        max_area = std::max(max_area, area);
      }
    }

    return max_area;
  }
};
