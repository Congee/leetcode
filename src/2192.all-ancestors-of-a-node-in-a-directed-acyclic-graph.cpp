#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  vector<vector<int>> getAncestors(int n, vector<vector<int>> &edges) {
    std::unordered_map<int, std::vector<int>> adjacency;
    std::unordered_map<int, int> indegrees;
    for (auto &&edge : edges) {
      auto from = edge[0];
      auto to = edge[1];
      adjacency[from].push_back(to);
      indegrees.try_emplace(from, 0);
      indegrees[to]++;
    }

    std::queue<int> queue;
    for (auto &&[k, v] : indegrees)
      if (v == 0) queue.push(k);

    std::vector<std::vector<int>> vec(n);
    std::unordered_map<int, std::unordered_set<int>> map;

    while (queue.size()) {
      auto curr = queue.front();
      queue.pop();

      for (auto &&nb : adjacency[curr]) {
        map[nb].insert(curr);
        map[nb].insert(map[curr].begin(), map[curr].end());
        if (--indegrees[nb] == 0) {
          queue.push(nb);
        }
      }
    }

    for (int i = 0; i < n; ++i) {
      auto it = map.find(i);
      if (it == map.end()) continue;
      vec[i].assign(map[i].begin(), map[i].end());
      std::sort(vec[i].begin(), vec[i].end());
    }

    return vec;
  }
};
