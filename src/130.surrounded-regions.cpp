#ifdef __LOCAL__
#include <leetcode.h>
#endif

static const auto dirs =
  std::vector<std::pair<int, int>>{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

class Solution {
  std::vector<int> root;
  std::vector<int> rank;

  int find(int x) {
    if (x == root[x]) return x;
    return root[x] = find(root[x]);
  }

  void connect(int x, int y) {
    auto root_x = find(root[x]);
    auto root_y = find(root[y]);

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
  void solve(vector<vector<char>>& board) {
    int m = board.size();
    int n = board[0].size();

    root.resize(m * n);
    for (int i = 0; i < m * n; ++i) root[i] = i;
    rank.assign(m * n, 0);

    const auto is_border = [&](int row, int col) {
      return row == 0 || row == m - 1 || col == 0 || col == n - 1;
    };
    const auto within = [&](int row, int col) {
      return row >= 0 && col >= 0 && row <= m - 1 && col <= n - 1;
    };

    std::unordered_set<int> border_cells;
    // [
    // ["O","X","X","O","X"],
    // ["X","O","O","X","O"],
    // ["X","O","X","O","X"],
    // ["O","X","O","O","O"],
    // ["X","X","O","X","O"]]

    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        if (board[r][c] == 'X') continue;
        if (is_border(r, c)) {
          border_cells.insert(r * n + c);
        }

        for (auto&& [dr, dc] : dirs) {
          int xr = r + dr;
          int xc = c + dc;
          if (!within(xr, xc)) continue;
          if (board[xr][xc] == 'X') continue;
          connect(r * n + c, xr * n + xc);
        }
      }
    }

    std::unordered_set<int> bad;
    for (auto&& cell : border_cells) bad.insert(find(cell));

    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        if (board[r][c] == 'X') continue;

        auto x = find(r * n + c);
        if (bad.count(x)) continue;

        int row = x / n;
        int col = x % n;
        if (is_border(row, col)) continue;
        board[r][c] = 'X';
      }
    }
  }
};
