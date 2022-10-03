#ifdef __LOCAL__
#include <leetcode.h>
#endif

using Pair = std::pair<int, int>;
static const auto dirs = std::vector<Pair>{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

class Solution {
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
  int closedIsland(vector<vector<int>>& grid) {
    // 1. find all islands
    // 2. exclude islands that are not closed
    // a not closed island means a board land can connect to it
    int m = grid.size();
    int n = grid[0].size();

    root.resize(m * n);
    for (int i = 0; i < m * n; ++i) root[i] = i;
    rank.assign(m * n, 0);

    auto on_border = [&](int row, int col) {
      return row == 0 || col == 0 || row == m - 1 || col == n - 1;
    };

    auto within = [&](int row, int col) {
      return row >= 0 && col >= 0 && row < m && col < n;
    };

    std::unordered_set<int> border_cells;

    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        if (grid[r][c] == 1) continue;

        if (on_border(r, c)) border_cells.insert(r * n + c);

        for (auto&& [dr, dc] : dirs) {
          auto xr = r + dr;
          auto xc = c + dc;
          if (!within(xr, xc)) continue;
          if (grid[xr][xc] == 1) continue;

          connect(r * n + c, xr * n + xc);
        }
      }
    }

    std::unordered_set<int> bad;
    for (auto cell : border_cells) bad.insert(find(cell));

    std::unordered_set<int> good;
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        if (grid[r][c] == 1) continue;
        auto found = find(r * n + c);
        if (!bad.count(found)) good.insert(found);
      }
    }

    return good.size();
  }
};
