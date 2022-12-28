#ifdef __LOCAL__
#include <leetcode.h>
#endif

using Grid = vector<vector<int>>;
using Pair = std::pair<int, int>;
const Pair dirs[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

class Solution {
  int m;
  int n;

  const std::string to_string(vector<vector<int>>& board) const {
    std::string str;
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        str += std::to_string(board[r][c]);
      }
    }
    return str;
  }

 public:
  int slidingPuzzle(vector<vector<int>>& board) {
    // this is similar to the Open Lock question
    // do BFS to find the shorted path from `board` to the end condition

    m = board.size();
    n = board[0].size();

    return bfs(board);
  }

  int bfs(vector<vector<int>>& board) {
    auto initstr = to_string(board);
    int start = initstr.find_first_of('0');
    std::queue<std::tuple<int, Grid, int>> queue({{start, board, 0}});
    std::unordered_set<std::string> seen({initstr});

    auto is_valid = [&](int row, int col) {
      return row < m && row >= 0 && col < n && col >= 0;
    };

    while (queue.size()) {
      auto [pos, grid, count] = queue.front();
      queue.pop();
      int row = pos / n;
      int col = pos % n;

      if (to_string(grid) == "123450"s) return count;

      for (auto&& [dr, dc] : dirs) {
        int r = row + dr;
        int c = col + dc;
        if (!is_valid(r, c)) continue;

        Grid copy = grid;
        std::swap(copy[r][c], copy[row][col]);
        auto str = to_string(copy);
        if (seen.count(str)) continue;
        queue.emplace(r * n + c, copy, count + 1);
        seen.insert(str);
      }
    }

    return -1;
  }
};
