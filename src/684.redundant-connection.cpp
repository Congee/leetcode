#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  std::vector<int> root;
  std::vector<int> rank;

  int find(int x) {
    if (x == root[x]) return x;
    return root[x] = find(root[x]);
  }

  bool connect(int x, int y) {
    auto root_x = find(root[x]);
    auto root_y = find(root[y]);

    if (root_x == root_y) return false;
    if (rank[root_x] < rank[root_y])
      root[root_x] = root_y;
    else if (rank[root_x] > rank[root_y])
      root[root_x] = root_y;
    else {
      root[root_y] = root_x;
      rank[root_x]++;
    }

    return true;
  }

 public:
  vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    std::unordered_map<int, std::vector<int>> adj;
    int n = -1;  // 1-based index
    for (auto&& edge : edges) {
      auto&& from = edge[0];
      auto&& to = edge[1];
      adj[from].push_back(to);
      n = std::max({n, from, to});
    }
    root.resize(n);
    for (int i = 0; i < n; ++i) root[i] = i;
    rank.assign(n, 0);

    std::vector<int> result;

    for (auto&& edge : edges) {
      auto&& from = edge[0];
      auto&& to = edge[1];
      if (!connect(from - 1, to - 1)) result = edge;
    }

    return result;
  }
};
