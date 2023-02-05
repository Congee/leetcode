#ifdef __LOCAL__
#include <leetcode.h>
#endif

using Pair = std::pair<int, int>;
const Pair dirs[] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};

class Solution {
 public:
  vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
    int m = heights.size(), n = heights[0].size();
    std::vector<std::vector<char>> mat(m, std::vector<char>(n));  // ['P', 'A']
    std::vector<std::vector<int>> result;

    std::queue<std::pair<int, int>> pqueue;
    std::queue<std::pair<int, int>> aqueue;

    for (int c = 0; c < n; ++c) pqueue.push({0, c});
    for (int r = 1; r < m; ++r) pqueue.push({r, 0});
    for (int c = 1; c < n; ++c) aqueue.push({m - 1, c});
    for (int r = 1; r < m - 1; ++r) pqueue.push({r, n - 1});

    auto within = [&](int row, int col) {
      return row >= 0 && row < m && col >= 0 && col < n;
    };

    while (pqueue.size()) {
      auto [row, col] = pqueue.front();
      pqueue.pop();

      if (row == 0 || col == 0) mat[row][col] = 'P';

      for (auto [dr, dc] : dirs) {
        int r = row + dr;
        int c = col + dc;
        if (!within(r, c)) continue;
        if (mat[r][c] == 'P') continue;

        if (heights[r][c] >= heights[row][col]) {
          mat[r][c] = 'P';
          pqueue.push({r, c});
        }
      }
    }

    while (aqueue.size()) {
      auto [row, col] = aqueue.front();
      aqueue.pop();

      if (row == m - 1 || col == n - 1) mat[row][col] = 'A';

      for (auto [dr, dc] : dirs) {
        int r = row + dr;
        int c = col + dc;
        if (!within(r, c)) continue;
        if (mat[r][c] == 'A') continue;

        if (heights[r][c] >= heights[row][col]) {
          if (mat[r][c] == 'P') result.push_back({r, c});
          aqueue.push({r, c});
        }
      }
    }

    return result;
  }
};
