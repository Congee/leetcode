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

struct Sofar {
  int dist;
  std::string instructions;
};

class Solution {
  int m;
  int n;
  Grid maze;
  const std::vector<pair<char, Pair>> dirs{
    {'u', {-1, 0}}, {'r', {0, 1}}, {'d', {1, 0}}, {'l', {0, -1}}};

 public:
  string findShortestWay(
    vector<vector<int>>& __maze, vector<int>& ball, vector<int>& hole
  ) {
    maze = std::move(__maze);
    m = maze.size();
    n = maze[0].size();

    return bfs(ball[0] * n + ball[1], hole[0] * n + hole[1]);
  }

  std::string bfs(int src, int dst) {
    // <pos, count, instructions>
    std::queue<std::tuple<int, int, std::string>> queue({{src, 0, ""s}});
    std::unordered_map<int, Sofar> cache({{src, Sofar{0, ""}}});  // <pos, >

    while (queue.size()) {
      auto [curr, cnt, instructions] = queue.front();
      queue.pop();

      for (auto&& [inst, delta] : dirs) {
        auto [dr, dc] = delta;
        int r = curr / n;
        int c = curr % n;
        int count = cnt;
        while (is_valid(r + dr, c + dc)) {
          r += dr;
          c += dc;
          count++;
          if (r * n + c == dst) break;
        }

        if (!is_valid(r, c)) continue;
        auto it = cache.find(r * n + c);
        // cmp = in case of dups
        if (it != cache.end()) {
          if (count > it->second.dist) continue;
          if (count == it->second.dist && instructions + inst > it->second.instructions)
            continue;
        }

        queue.emplace(r * n + c, count, instructions + inst);
        cache.insert_or_assign(r * n + c, Sofar{count, instructions + inst});
      }
    }

    auto it = cache.find(dst);
    return it == cache.end() ? "impossible" : it->second.instructions;
  }

  bool is_valid(int row, int col) const {
    return row >= 0 && row < m && col >= 0 && col < n && maze[row][col] != WALL;
  }
};

// [[0,1,0,0,1,0,0,1,0,0]
// ,[0,0,1,0,0,1,0,0,1,0]
// ,[0,0,0,0,*,0,1,0,0,1]
// ,[0,0,0,0,0,0,1,0,0,1]
// ,[0,1,0,0,1,0,0,1,0,0]
// ,[0,0,1,0,0,1,0,0,0,0]
// ,[0,0,0,0,0,0,1,0,0,0]
// ,[1,0,0,1,0,0,x,0,0,1]
// ,[0,1,0,0,1,0,0,1,0,0]
// ,[0,0,0,0,0,1,0,0,1,0]]
// ball = [2,4]
// hole = [7,6]
