#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  std::vector<std::vector<int>> adj;
  vector<vector<int>> edges;
  int n;
  int max_diameter;

 public:
  int treeDiameter(vector<vector<int>>& __edges) {
    // NOTE: it's an acyclic graph
    // -----*--------------
    //     /
    //    /
    //   /

    if (__edges.empty()) return 0;

    edges = std::move(__edges);
    n = edges.size() + 1;
    adj = std::vector<std::vector<int>>(n, std::vector<int>());
    for (auto&& edge : edges) {
      adj[edge[0]].push_back(edge[1]);
      adj[edge[1]].push_back(edge[0]);
    }

    // dfs(0);
    // return max_diameter;

    auto farthest = bfs(0).second;
    return bfs(farthest).first;
  }

  int dfs(int node, int parent = -1) {
    if (adj[node].empty()) return 0;

    int max = 0;
    int snd = 0;
    for (auto nb : adj[node]) {
      if (nb == parent) continue;

      auto level = dfs(nb, node);
      if (level > max) {
        auto prev_max = max;  // in case level is incrementally greater than max
                              // in this loop, like level=7,8,9,10 > max=5
        max = level;
        if (prev_max > snd) snd = prev_max;
      } else if (level > snd) {
        snd = level;
      }
      max_diameter = std::max(max_diameter, max + snd);
    }
    return max + 1;
  }

  // 1. start from an arbitrary node, find the farthest node
  // 2. start from the farthest node to the end
  std::pair<int, int> bfs(int start) {
    std::queue<std::pair<int, int>> queue({{start, 0}});
    std::vector<bool> seen(n, false);
    seen[start] = true;
    int max_level = 0, farthest = -1;
    while (queue.size()) {
      auto [node, level] = queue.front();
      queue.pop();

      if (level > max_level) {
        max_level = level;
        farthest = node;
      }

      for (auto&& nb : adj[node]) {
        if (seen[nb]) continue;
        queue.emplace(nb, level + 1);
        seen[nb] = true;
      }
    }
    return {max_level, farthest};
  }
};
