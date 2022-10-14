#ifdef __LOCAL__
#include <leetcode.h>
#endif

using Pair = std::pair<int, int>;
const Pair dirs[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

class Solution {
  vector<vector<int>> heights;
  int m;
  int n;
  vector<vector<int>> memo;
  vector<vector<bool>> seen;

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

  inline bool within(int row, int col) const {
    return row >= 0 && col >= 0 && row < m && col < n;
  }

 public:
  int minimumEffortPath(vector<vector<int>>& __heights) {
    heights = std::move(__heights);
    m = heights.size();
    n = heights[0].size();

    return prim();
    return kruskal();
    return binary_search();
    return spfa();
    return dijkstra();
  }

  int kruskal() {
    root.resize(m * n);
    rank.assign(m * n, 0);
    std::vector<std::tuple<int, int, int>> edges;
    for (int row = 0; row < m; ++row) {
      for (int col = 0; col < n; ++col) {
        root[row * n + col] = row * n + col;

        for (auto&& [dr, dc] : dirs) {
          int r = row + dr;
          int c = col + dc;
          if (!within(r, c)) continue;

          int diff = std::abs(heights[row][col] - heights[r][c]);
          edges.emplace_back(diff, row * n + col, r * n + c);
        }
      }
    }
    std::sort(edges.begin(), edges.end());

    int min_effort = 0;  // m == n == 1
    for (auto&& [diff, from, to] : edges) {
      connect(from, to);
      min_effort = std::max(min_effort, diff);
      if (find(0) == find(m * n - 1)) return min_effort;
    }

    return min_effort;
  }

  int binary_search() const {
    int min = INT_MAX;
    int max = INT_MIN;
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        min = std::min(min, heights[r][c]);
        max = std::max(max, heights[r][c]);
      }
    }

    int lo = 0;
    int hi = max - min;

    int min_effort = INT_MAX;
    // lo ---goal+mid++++hi
    while (lo <= hi) {
      int mid = lo + (hi - lo) / 2;

      if (bfs(mid)) {
        hi = mid - 1;
        min_effort = mid;
      } else {
        lo = mid + 1;
      }
    }
    return min_effort;
  }

  inline bool bfs(int mid) const {
    std::vector<bool> seen(m * n, 0);
    std::queue<int> queue({0});

    while (queue.size()) {
      auto curr = queue.front();
      queue.pop();

      if (curr == m * n - 1) return true;
      int row = curr / n;
      int col = curr % n;

      for (auto&& [dr, dc] : dirs) {
        int r = row + dr;
        int c = col + dc;
        if (!within(r, c)) continue;

        auto nb = r * n + c;
        if (seen[nb]) continue;

        if (std::abs(heights[r][c] - heights[row][col]) <= mid) {
          queue.push(nb);
          seen[nb] = 1;  // XXX: must be put here
        }
      }
    }

    return false;
  }

  int dijkstra() {
    std::vector<int> table(m * n, INT_MAX);  // <diff, from>
    table[0] = 0;

    std::vector<bool> seen(m * n, 0);
    std::priority_queue<Pair, vector<Pair>, std::greater<Pair>> pq;
    pq.emplace(0, 0);

    while (pq.size()) {
      auto [diff, curr] = pq.top();
      pq.pop();
      int row = curr / n;
      int col = curr % n;

      seen[curr] = 1;
      if (curr == m * n - 1) return diff;

      for (auto [dr, dc] : dirs) {
        int r = row + dr;
        int c = col + dc;
        auto nb = r * n + c;

        if (!within(r, c)) continue;
        if (seen[nb]) continue;

        int delta = std::max(diff, std::abs(heights[row][col] - heights[r][c]));
        if (delta < table[nb]) {
          table[nb] = delta;
          pq.emplace(delta, nb);
        }
      }
    }

    return table.back();
  }

  int prim() {
    // min heap to always use the edge of minimum weight
    // keep connecting until we meet the target
    // <weight, vertex>
    auto cmp = [&](const Pair& lhs, const Pair& rhs) {
      return lhs.first > rhs.first;  // XXX: do not use std::greater<Pair>
    };
    std::priority_queue<Pair, vector<Pair>, decltype(cmp)> pq(cmp);
    pq.emplace(0, 0);
    std::vector<bool> seen(m * n, 0);
    seen[0] = 1;
    int min_effort = 0;
    while (pq.size()) {
      auto [diff, curr] = pq.top(); pq.pop();

      if (curr == m * n - 1) return diff;
      seen[curr] = 1;  // XXX: must be put here
      int row = curr / n;
      int col = curr % n;

      for (auto&& [dr, dc] : dirs) {
        int r = row + dr;
        int c = col + dc;
        if (!within(r, c)) continue;

        auto nb = r * n + c;
        if (seen[nb]) continue;

        int delta = std::max(diff, std::abs(heights[row][col] - heights[r][c]));
        pq.emplace(delta, nb);
      }
    }

    return min_effort;
  }

  int spfa() {
    std::vector<int> dist(m * n, INT_MAX);
    dist[0] = 0;

    std::queue<int> queue({0});
    while (queue.size()) {
      auto curr = queue.front();
      queue.pop();

      int row = curr / n;
      int col = curr % n;

      for (auto&& [dr, dc] : dirs) {
        int r = row + dr;
        int c = col + dc;
        if (!within(r, c)) continue;

        const auto nb = r * n + c;
        int delta = max(dist[curr], abs(heights[row][col] - heights[r][c]));
        if (delta < dist[nb]) {
          dist[nb] = delta;
          queue.push(nb);
        }
      }
    }

    return dist.back();
  }

  // wrong
  int dp() {
    memo.assign(m, std::vector<int>(n, 0));
    seen.assign(m, std::vector<bool>(n, 0));
    memo.back().back() = 0;
    seen[0][0] = 1;

    return dfs(0, 0);
  }

  int dfs(int row, int col) {
    if (memo[row][col]) return memo[row][col];

    int min_effort = INT_MAX;

    for (auto&& [dr, dc] : dirs) {
      auto xr = row + dr;
      auto xc = col + dc;
      if (!within(xr, xc)) continue;
      if (seen[xr][xc]) continue;

      seen[xr][xc] = 1;
      auto diff = std::abs(heights[row][col] - heights[xr][xc]);
      min_effort = std::min(min_effort, std::max(diff, dfs(xr, xc)));
    }

    return memo[row][col] = min_effort;
  }
};
