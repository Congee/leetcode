#ifdef __LOCAL__
#include <leetcode.h>
#endif

using Pair = std::pair<int, int>;

#if 0
class Solution {
 public:
  // Add a virtual vertex and connect to the rest. The weight of each edge is
  // the weight the edge expands to
  int minCostToSupplyWater(
    int n, vector<int>& wells, vector<vector<int>>& pipes
  ) {
    wells.push_back(0);
    // <to, <from, weight>>
    std::vector<std::vector<std::pair<int, int>>> adj(n + 1);
    for (auto&& p : pipes) {
      auto x = p[0] - 1;
      auto y = p[1] - 1;
      auto weight = p[2];
      adj[x].emplace_back(y, weight);
      adj[y].emplace_back(x, weight);
    }
    // connect to the virtual vertex
    for (int i = 0; i < n; ++i) {
      adj[n].emplace_back(i, wells[i]);
      adj[i].emplace_back(n, wells[i]);
    }

    // <weight, vertex>
    std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> pq;
    pq.emplace(0, n);
    std::vector<bool> seen(n + 1, 0);

    int min_cost = 0;
    int count = 0;
    while (count < n + 1) {
      auto [weight, vertex] = pq.top();
      pq.pop();

      if (seen[vertex]) continue;

      seen[vertex] = true;
      min_cost += weight;
      count++;

      for (auto&& [nb, nb_weight] : adj[vertex]) {
        if (!seen[nb]) pq.emplace(nb_weight, nb);
      }
    }

    return min_cost;
  }
};
#endif

#if 1
class Solution {
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
  // as long as it's cheaper to connect, don't build
  int minCostToSupplyWater(
    int n, vector<int>& wells, vector<vector<int>>& pipes
  ) {
    wells.push_back(0);  // virtual vertex
    root.resize(n + 1);
    rank.assign(n + 1, 0);

    for (int i = 0; i < n + 1; ++i) root[i] = i;

    for (int i = 0; i < n; ++i) pipes.push_back({i + 1, n + 1, wells[i]});

    std::sort(
      pipes.begin(), pipes.end(),
      [&](const auto& lhs, const auto& rhs) { return lhs.back() < rhs.back(); }
    );

    // <to, <from, weight>>
    std::vector<std::vector<std::pair<int, int>>> adj(n + 1);
    for (auto&& p : pipes) {
      auto x = p[0] - 1;
      auto y = p[1] - 1;
      auto weight = p[2];
      adj[x].emplace_back(y, weight);
      adj[y].emplace_back(x, weight);
    }

    int min_cost = 0;
    int count = 0;

    for (auto&& p : pipes) {
      auto x = p[0] - 1;
      auto y = p[1] - 1;
      auto weight = p[2];
      if (!connect(x, y)) {
        // did connect
        count++;
        min_cost += weight;
      }

      if (count == n) break;
    }

    return min_cost;
  }
};
#endif

#if 0
5
[3,7,5,2,2]
[[2,1,2],[3,2,9],[5,3,3]]
6
[1,2,9,4,7,3]
[[2,1,4],[3,1,1],[4,1,3],[5,3,8],[6,1,2]]
#endif
