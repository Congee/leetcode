#ifdef __LOCAL__
#include <leetcode.h>
#endif

const std::pair<int, int> dirs[] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

class Solution {
  int m, n;
  vector<vector<int>> matrix;

  inline auto is_valid(int row, int col) -> bool {
    return row >= 0 && row < m && col >= 0 && col < n;
  };

 public:
  int longestIncreasingPath(vector<vector<int>>& __matrix) {
    matrix = std::move(__matrix);
    m = matrix.size(), n = matrix[0].size();
    return topo_kahn();
    return by_dfs();
    return bfs();
  }

  int dynamic_programming() {
    // dp[r][c] = max(dp[r][c], dp[nr][nc] + 1) for all good neighbors (nr, nc)
    // where good means matrix[nr][nc] > matrix[r][c];
    std::vector<std::tuple<int, int, int>> nodes;
    for (int row = 0; row < m; ++row) {
      for (int col = 0; col < n; ++col) {
        nodes.emplace_back(-matrix[row][col], row, col);  // backwards
      }
    }
    std::sort(nodes.begin(), nodes.end());

    int max = 1;
    vector<vector<int>> dp(m, std::vector<int>(n, 1));
    for (auto [_, row, col] : nodes) {
      for (auto [dr, dc] : dirs) {
        int r = row + dr;
        int c = col + dc;
        if (!is_valid(r, c)) continue;
        if (matrix[r][c] <= matrix[row][col]) continue;

        dp[row][col] = std::max(dp[row][col], dp[r][r] + 1);
      }
      max = std::max(max, dp[row][col]);
    }

    return max;
  }

  int topo_kahn() {
    vector<vector<int>> indegrees(m, std::vector<int>(n));

    std::queue<std::pair<int, int>> queue;
    for (int row = 0; row < m; ++row) {
      for (int col = 0; col < n; ++col) {
        for (auto [dr, dc] : dirs) {
          int r = row + dr;
          int c = col + dc;
          if (!is_valid(r, c)) continue;
          indegrees[row][col] += matrix[r][c] < matrix[row][col];
        }
        if (indegrees[row][col] == 0) queue.emplace(row, col);
      }
    }

    int steps = 0;
    while (queue.size()) {
      steps++;
      const int size = queue.size();

      for (int i = 0; i < size; ++i) {
        auto [row, col] = queue.front();
        queue.pop();

        for (auto [dr, dc] : dirs) {
          int r = row + dr;
          int c = col + dc;
          if (!is_valid(r, c)) continue;
          if (matrix[r][c] <= matrix[row][col]) continue;
          if (--indegrees[r][c] == 0) queue.emplace(r, c);
        }
      }
    }

    return steps;
  }

  int by_dfs() {
    vector<vector<int>> memo(m, std::vector<int>(n));
    int best = 1;
    for (int row = 0; row < m; ++row) {
      for (int col = 0; col < n; ++col) {
        best = std::max(best, dfs(row, col, memo));
      }
    }

    return best;
  }

  int dfs(int row, int col, vector<vector<int>>& memo) {
    if (memo[row][col]) return memo[row][col];

    for (auto [dr, dc] : dirs) {
      int r = row + dr;
      int c = col + dc;
      if (!is_valid(r, c)) continue;
      if (matrix[row][col] >= matrix[r][c]) continue;

      memo[row][col] = std::max(memo[row][col], dfs(r, c, memo));
    }

    return ++memo[row][col];
  }

  int bfs() {
    // bfs + memoization
    // start bfs on every node
    // if the memoized value is less than the search steps, go, otherwise stop
    int best = 1;
    vector<vector<int>> memo(m, std::vector<int>(n, 1));

    for (int row = 0; row < m; ++row) {
      for (int col = 0; col < n; ++col) {
        if (memo[row][col] > 1) continue;

        std::queue<std::pair<int, int>> queue({{row, col}});

        int steps = 1;
        while (queue.size()) {
          const int size = queue.size();
          for (int i = 0; i < size; ++i) {
            auto [r, c] = queue.front();
            queue.pop();

            for (auto [dr, dc] : dirs) {
              int nr = r + dr;
              int nc = c + dc;
              if (!is_valid(nr, nc)) continue;
              if (matrix[nr][nc] <= matrix[r][c]) continue;
              if (memo[nr][nc] >= steps + 1) continue;

              memo[nr][nc] = steps + 1;
              best = std::max(best, steps + 1);
              queue.emplace(nr, nc);
            }
          }

          steps++;
        }
      }
    }

    return best;
  }
};
