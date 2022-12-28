#ifdef __LOCAL__
#include <leetcode.h>
#endif

enum {
  EMPTY = 0,
  WALL = 1,
  HOLE = 2,
};
using Pair = std::pair<int, int>;
using Grid = vector<vector<int>>;
const Pair dirs[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

class Solution {
  int m;
  int n;
  Grid maze;

 public:
  bool hasPath(
    vector<vector<int>>& __maze, vector<int>& start, vector<int>& destination
  ) {
    maze = std::move(__maze);
    m = maze.size();
    n = maze[0].size();

    return bfs(start[0] * n + start[1], destination[0] * n + destination[1]) !=
           -1;
  }

  int bfs(int src, int dst) {
    std::queue<Pair> queue({{src, 0}});  // <source, count>
    std::vector<bool> seen(n * m, false);
    seen[src] = true;

    while (queue.size()) {
      auto [curr, cnt] = queue.front();
      queue.pop();

      for (auto&& [dr, dc] : dirs) {
        int r = curr / n;
        int c = curr % n;
        int count = cnt;
        for (; is_valid(r + dr, c + dc); r += dr, c += dc, count++)
          ;

        if (!is_valid(r, c)) continue;
        if (r * n + c == dst) return count;
        if (seen[r * n + c]) continue;

        queue.emplace(r * n + c, count);
        seen[r * n + c] = true;
      }
    }

    return -1;
  }

  bool is_valid(int row, int col) const {
    return row >= 0 && row < m && col >= 0 && col < n && maze[row][col] != WALL;
  }
};
