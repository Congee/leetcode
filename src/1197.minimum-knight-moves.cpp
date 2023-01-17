#ifdef __LOCAL__
#include <leetcode.h>
#endif

const std::pair<int, int> dirs[] = {
  {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}};

class Solution {
  auto is_valid(int row, int col) -> bool {
    bool in_board = row >= -300 && row <= 300 && col >= -300 && col <= 300;
    int sum = std::abs(row) + std::abs(col);
    bool in_range = 0 <= sum && sum <= 300;
    return in_board && in_range;
  };

  auto oppo_quadrant(int row, int col, int x, int y) -> bool {
    return row * x < 0 && col * y < 0;
  };

  inline int key_of(int r, int c) { return (r + 301) * 601 + (c + 301); }

 public:
  int minKnightMoves(int x, int y) {
    return bidirectional_bfs(x, y);
    return bfs(x, y);
  }

  int bidirectional_bfs(int x, int y) {
    if (x == 0 && y == 0) return 0;
    // just bfs to find the target
    std::queue<std::pair<int, int>> squeue({{0, 0}}), tqueue({{x, y}});
    std::vector<bool> sseen(1e7), tseen(1e7);  // 12MB / 8 * 2
    sseen[key_of(0, 0)] = true;
    tseen[key_of(x, y)] = true;

    auto search = [&](
                    std::queue<std::pair<int, int>>& queue,
                    std::vector<bool>& seen,
                    std::vector<bool>& other_seen
                  ) -> bool {
      const int size = queue.size();
      for (int i = 0; i < size; ++i) {
        auto [row, col] = queue.front();
        queue.pop();

        for (auto [dr, dc] : dirs) {
          int r = row + dr;
          int c = col + dc;
          if (!is_valid(r, c)) continue;
          // NOTE: we can also prune due to symmetry
          if (oppo_quadrant(r, c, x, y)) continue;

          const auto key = key_of(r, c);
          if (seen[key]) continue;
          if (other_seen[key]) return true;

          seen[key] = true;
          queue.emplace(r, c);
        }
      }
      return false;
    };

    int steps = 0;
    while (squeue.size() && tqueue.size()) {
      steps++;
      if (search(squeue, sseen, tseen)) return steps;
      steps++;
      if (search(tqueue, tseen, sseen)) return steps;
    }

    return -1;
  }

  int bfs(int x, int y) {
    if (x == 0 && y == 0) return 0;
    // just bfs to find the target
    std::queue<std::pair<int, int>> queue({{0, 0}});
    std::vector<bool> seen(1e7);  // 12MB / 8

    auto is_valid = [](int row, int col) {
      bool in_board = row >= -300 && row <= 300 && col >= -300 && col <= 300;
      int sum = std::abs(row) + std::abs(col);
      bool in_range = 0 <= sum && sum <= 300;
      return in_board && in_range;
    };

    auto oppo_quadrant = [](int row, int col, int x, int y) {
      return row * x < 0 && col * y < 0;
    };

    int steps = 0;
    while (queue.size()) {
      const int size = queue.size();
      for (int i = 0; i < size; ++i) {
        auto [row, col] = queue.front();
        queue.pop();

        for (auto [dr, dc] : dirs) {
          int r = row + dr;
          int c = col + dc;
          if (!is_valid(r, c)) continue;
          // NOTE: we can also prune due to symmetry
          if (oppo_quadrant(r, c, x, y)) continue;

          const auto key = (r + 301) * 601 + (c + 301);
          if (seen[key]) continue;
          if (r == x && c == y) return steps + 1;

          seen[key] = true;
          queue.emplace(r, c);
        }
      }

      steps++;
    }

    return -1;
  }
};
