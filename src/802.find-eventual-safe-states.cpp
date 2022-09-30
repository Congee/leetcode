#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
    return kahn(graph);
    return dfs_wrapper(graph);
  }

  vector<int> dfs_wrapper(vector<vector<int>>& graph) {
    std::vector<int> vec;
    std::vector<int> memo(graph.size(), -1);
    std::vector<int> seen(graph.size(), 0);  // cycle
    for (size_t i = 0; i < graph.size(); ++i) {
      if (dfs(i, graph, memo, seen)) vec.push_back(i);
    }

    return vec;
  }

  template <typename M, typename S>
  bool dfs(int i, vector<vector<int>>& graph, M& memo, S& seen) {
    if (graph[i].empty()) return true;
    if (memo[i] != -1) return memo[i];
    if (seen[i]) return false;
    seen[i] = true;

    // clang-format off
    return memo[i] = std::all_of(
      graph[i].begin(),
      graph[i].end(),
      [&](const auto& next) { return dfs(next, graph, memo, seen); }
    );
    // clang-format on
  }

  vector<int> kahn(vector<vector<int>>& graph) {
    // Kahn's
    // reverse all the directions
    // answers are nodes that will eventuall have an indegree 0
    //
    // doen't work with intermediate nodes

    std::unordered_map<int, int> indegrees;
    std::unordered_map<int, std::vector<int>> adjacency;
    for (size_t i = 0; i < graph.size(); ++i) {
      for (auto node : graph[i]) {
        adjacency[node].push_back(i);
        indegrees.try_emplace(node, 0);
        indegrees[i]++;
      }
      indegrees.try_emplace(i, 0);
    }

    std::vector<int> vec;
    std::queue<int> queue;
    for (auto&& [k, v] : indegrees) {
      if (v == 0) {
        queue.push(k);
        vec.push_back(k);
      }
    }

    while (queue.size()) {
      auto curr = queue.front();
      queue.pop();

      for (auto nb : adjacency[curr]) {
        if (--indegrees[nb] == 0) {
          queue.push(nb);
          vec.push_back(nb);
        }
      }
    }

    std::sort(vec.begin(), vec.end());
    return vec;
  }
};
