#ifdef __LOCAL__
#include <leetcode.h>
#endif

// N E S W
static const auto dirs =
  std::vector<std::pair<int, int>>{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

class UnionFind {
  std::vector<int> root;
  std::vector<int> rank;

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

 public:
  int maxAreaOfIsland(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    root.reserve(m * n);
    rank.assign(m * n, 0);

    bool has = false;
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        if (grid[r][c] == 0) continue;
        root[r * n + c] = r * n + c;
        has = true;
      }
    }
    if (has == false) return 0;

    auto is_valid = [&](int row, int col) {
      bool in = row >= 0 && col >= 0 && row < m && col < n;
      return in && grid[row][col] == 1;
    };

    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        if (grid[r][c] == 0) continue;

        // 1 1 0
        // 0 1 1
        for (auto&& [dr, dc] : dirs) {
          auto xr = r + dr;
          auto xc = c + dc;
          if (is_valid(xr, xc)) {
            connect(r * n + c, xr * n + xc);
          }
        }
      }
    }

    std::unordered_map<int, int> counter;  // <loc, count>
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        if (grid[r][c] == 0) continue;
        counter[find(r * n + c)]++;
      }
    }

    auto it = std::max_element(
      counter.begin(), counter.end(),
      [&](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; }
    );

    return it->second;
  }
};

class Solution {
  vector<vector<int>> grid;
  vector<vector<bool>> seen;
  int m;
  int n;
  int max_area = 0;

 public:
  int maxAreaOfIsland(vector<vector<int>>& __grid) {
    grid = std::move(__grid);
    m = grid.size();
    n = grid[0].size();
    seen.assign(m, std::vector<bool>(n, 0));
    return dfs_wrapper();

    return UnionFind().maxAreaOfIsland(grid);
  }

  int dfs_wrapper() {
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        if (seen[r][c]) continue;
        if (grid[r][c] == 1) dfs(r, c);
      }
    }

    return max_area;
  }

  void dfs(int row, int col) {
    auto is_valid = [&](int r, int c) {
      bool in = r >= 0 && c >= 0 && r < m && c < n;
      return in && grid[r][c] == 1;
    };
    std::stack<std::tuple<int, int>> stack;
    stack.emplace(row, col);
    seen[row][col] = 1;
    int area = 0;
    while (stack.size()) {
      auto [r, c] = stack.top();
      stack.pop();
      max_area = std::max(max_area, ++area);

      for (auto&& [dr, dc] : dirs) {
        auto xr = r + dr;
        auto xc = c + dc;
        if (!is_valid(xr, xc)) continue;
        if (seen[xr][xc]) continue;

        stack.push({xr, xc});
        seen[xr][xc] = 1;
      }
    }
  }
};
