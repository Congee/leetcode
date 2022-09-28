#ifdef __LOCAL__
#include <leetcode.h>
#endif

using Pair = std::pair<int, int>;

class Solution {
  vector<vector<int>> connections;
  std::vector<std::vector<Pair>> adj;
  int n;

  std::vector<int> root;
  std::vector<int> rank;

  int find(int x) {
    if (x == root[x]) return x;
    return root[x] = find(root[x]);
  }

  bool connect(int x, int y) {
    auto root_x = find(x);
    auto root_y = find(y);

    if (root_x == root_y) return false;

    if (rank[root_x] < rank[root_y])
      root[root_x] = root_y;
    else if (rank[root_x] > rank[root_y])
      root[root_y] = root_x;
    else {
      root[root_y] = root_x;
      rank[root_x]++;
    }

    return true;
  }

 public:
  int minimumCost(int __n, vector<vector<int>>& __connections) {
    n = __n;
    adj.resize(n);
    connections = std::move(__connections);
    rank.assign(n, 0);
    root.resize(n);
    for (int i = 0; i < n; ++i) root[i] = i;

    std::sort(
      connections.begin(), connections.end(),
      [&](const auto& lhs, const auto& rhs) { return lhs.back() < rhs.back(); }
    );

    return kruskal();
  }

  int kruskal() {
    int count = 0;
    int min_cost = 0;

    for (size_t i = 0; i < connections.size() && count < n - 1; ++i) {
      auto x = connections[i][0] - 1;
      auto y = connections[i][1] - 1;
      auto weight = connections[i][2];
      if (connect(x, y)) {
        count++;
        min_cost += weight;
      }
    }

    return count == n - 1 ? min_cost : -1;
  }
};

#if 0

class Solution {
  vector<vector<int>> connections;
  std::vector<std::vector<Pair>> adj;
  int n;

 public:
  int minimumCost(int __n, vector<vector<int>>& __connections) {
    n = __n;
    adj.resize(n);
    connections = std::move(__connections);
    for (size_t i = 0; i < connections.size(); ++i) {
      int x = connections[i][0] - 1;
      int y = connections[i][1] - 1;
      int weight = connections[i][2];
      adj[x].push_back({y, weight});
      adj[y].push_back({x, weight});
    }

    return prim();
  }

  int prim() {
    std::vector<int> seen(n, 0);
    int min_cost = 0;
    int count = 0;
    // <min weight, vertex>
    std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> pq;
    pq.push({0, 0});

    while (count < n) {
      if (pq.empty()) return -1;
      auto [weight, curr] = pq.top();
      pq.pop();

      if (seen[curr]) continue;

      seen[curr] = true;
      count++;
      min_cost += weight;

      for (auto&& [nb, nb_cost] : adj[curr]) {
        if (!seen[nb]) pq.push({nb_cost, nb});
      }
    }

    return min_cost;
  }
};
#endif
