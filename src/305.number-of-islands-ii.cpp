#ifdef __LOCAL__
#include <leetcode.h>
#endif

using Pair = std::pair<int, int>;
const Pair dirs[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

class Solution {
  std::vector<int> rank;
  std::unordered_map<int, int> root;  // exclusively for islands
  int count = 0;

  int find(int x) {
    if (root[x] == x) return x;
    return root[x] = find(root[x]);
  }

  void connect(int x, int y) {
    int root_x = find(x);
    int root_y = find(y);

    if (root_x == root_y) return;

    if (rank[root_x] < rank[root_y]) {
      rank[root_y]++;
      root[root_x] = root[root_y];
    } else if (rank[root_x] > rank[root_y]) {
      rank[root_x]++;
      root[root_y] = root[root_x];
    } else {
      rank[root_x]++;
      root[root_y] = root[root_x];
    }
    count--;
  }

 public:
  vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
    // UnionFind

    rank = std::vector<int>(m * n);

    auto is_valid = [&](int row, int col) -> bool {
      return row >= 0 && row < m && col >= 0 && col < n;
    };

    std::vector<int> islands;

    for (auto&& pos : positions) {
      int ri = pos[0], ci = pos[1];
      if (root.count(ri * n + ci)) {  // duplicate
        islands.push_back(count);
        continue;
      }

      root[ri * n + ci] = ri * n + ci;
      count++;

      for (auto [dr, dc] : dirs) {
        int r = ri + dr;  // neighbor
        int c = ci + dc;
        if (!is_valid(r, c)) continue;
        if (root.count(r * n + c)) connect(ri * n + ci, r * n + c);
      }

      islands.push_back(count);
    }

    return islands;
  }
};
