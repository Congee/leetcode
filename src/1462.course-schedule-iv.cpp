#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  std::unordered_map<int, std::unordered_set<int>> adjacency;
  std::vector<std::vector<int>> memo;

  auto find(int x, int y) -> bool {
    auto it = adjacency.find(x);
    if (it == adjacency.end()) return false;
    if (memo[x][y] != -1) return memo[x][y];

    // clang-format off
    return memo[x][y] = std::any_of(
      it->second.begin(),
      it->second.end(),
      [&](const auto& num) { return find(num, y); }
    );
    // clang-format on
  };

 public:
  vector<bool> checkIfPrerequisite(
    int numCourses,
    vector<vector<int>>& prerequisites,
    vector<vector<int>>& queries
  ) {
    return kahn(prerequisites, queries);
    return quick_find(numCourses, prerequisites, queries);
  }

  vector<bool> kahn(
    vector<vector<int>>& prerequisites, vector<vector<int>>& queries
  ) {
    // reverse edges
    std::unordered_map<int, std::vector<int>> adjacency;
    std::unordered_map<int, int> indegrees;

    for (auto&& pre : prerequisites) {
      auto from = pre[0];
      auto to = pre[1];
      adjacency[to].push_back(from);
      indegrees.try_emplace(from, 0);
      indegrees[to]++;
    }

    std::queue<int> queue;
    for (auto&& [k, v] : indegrees)
      if (v == 0) queue.push(k);

    std::unordered_map<int, std::unordered_set<int>> to_query;
    while (queue.size()) {
      auto curr = queue.front();
      queue.pop();

      for (auto&& nb : adjacency[curr]) {
        to_query[nb].insert(curr);
        to_query[nb].insert(to_query[curr].begin(), to_query[curr].end());
        if (--indegrees[nb] == 0) queue.push(nb);
      }
    }

    std::vector<bool> vec;
    for (auto&& q : queries) {
      vec.push_back(to_query[q[1]].count(q[0]));
    }
    return vec;
  }

  vector<bool> quick_find(
    int numCourses,
    vector<vector<int>>& prerequisites,
    vector<vector<int>>& queries
  ) {
    for (auto&& pre : prerequisites) adjacency[pre[0]].insert(pre[1]);
    memo.assign(numCourses, std::vector<int>(numCourses, -1));

    std::vector<bool> vec;
    for (auto&& q : queries) vec.push_back(find(q[0], q[1]));
    return vec;
  }
};
