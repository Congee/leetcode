#ifdef __LOCAL__
#include <leetcode.h>
#endif

using Pair = std::pair<int, int>;
const Pair dirs[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

class Solution {
 public:
  int shortestDistance(vector<vector<int>>& grid) {
    // optmize to avoid visiting bad cells. e.g., the right part or 1s will not
    // visit its neighbor 0s;
    //
    // 1 -1 2 0 x 1  -> the last 1 looks for -1
    // 1 -1 2 0 0 x  -> the first 1 looks for -2
    // 1 -1 2 0 0 0
    // 1 -1 2 0 0 0
    // 1 -1 2 0 0 0
    // 1 -1 2 0 0 0

    int m = grid.size(), n = grid[0].size(), target = 0, best = INT_MAX;
    std::vector<std::vector<int>> dist(m, std::vector<int>(n));

    auto is_valid = [&](int row, int col, int tg) {
      return row >= 0 && row < m && col >= 0 && col < n && grid[row][col] == tg;
    };

    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        if (grid[r][c] == 1) {
          best = INT_MAX;
          int steps = 0;
          std::queue<int> queue({r * n + c});
          while (queue.size()) {
            steps++;
            const int size = queue.size();
            for (int i = 0; i < size; ++i) {
              int curr = queue.front();
              queue.pop();
              for (auto [dr, dc] : dirs) {
                int r = curr / n + dr;
                int c = curr % n + dc;
                if (!is_valid(r, c, target)) continue;

                dist[r][c] += steps;
                grid[r][c]--;
                best = std::min(best, dist[r][c]);
                queue.push(r * n + c);
              }
            }
          }
          target--;
        }
      }
    }

    return best == INT_MAX ? -1 : best;
  }

  int tle(vector<vector<int>>& grid) {
    // do BFS starting from all houses
    int m = grid.size(), n = grid[0].size(), houses = 0;
    std::queue<Pair> queue;  // <start, curr>
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        if (grid[r][c] == 1) queue.push({r * n + c, r * n + c});
      }
    }
    houses = queue.size();

    auto is_valid = [&](int row, int col) {
      return row >= 0 && row < m && col >= 0 && col < n && grid[row][col] == 0;
    };
    std::vector<std::vector<int>> good(m, std::vector<int>(n));

    // <pos, <start, distance>>
    std::unordered_map<int, std::unordered_map<int, int>> dist;
    while (queue.size()) {
      auto [start, curr] = queue.front();
      queue.pop();

      int row = curr / n;
      int col = curr % n;
      for (auto [dr, dc] : dirs) {
        int r = row + dr;
        int c = col + dc;
        int neighbor = r * n + c;
        if (!is_valid(r, c)) continue;
        if (good[r][c]) continue;

        auto it = dist[neighbor].find(start);
        if (it != dist[neighbor].end()) continue;  // seen

        dist[neighbor][start] = dist[curr][start] + 1;
        if (dist[neighbor].size() == houses) good[r][c] = 1;
        queue.push({start, neighbor});
      }
    }

    int best = INT_MAX;
    for (auto&& [curr, map] : dist) {
      int r = curr / n;
      int c = curr % n;
      if (grid[r][c] == 1) continue;
      if (map.size() == houses) {
        int x = std::accumulate(
          map.begin(),
          map.end(),
          0,
          [&](int acc, const auto& p) { return acc + p.second; }
        );
        best = std::min(best, x);
      }
    }

    return best == INT_MAX ? -1 : best;
  }
};

#if 0
[
[1,1,1,1,1,0],
[0,0,0,0,0,1],
[0,1,1,0,0,1],
[1,0,0,1,0,1],
[1,0,1,0,x,1],
[1,0,0,0,0,1],
[0,1,1,1,1,0]]
#endif
