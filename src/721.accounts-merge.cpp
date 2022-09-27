#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  std::unordered_map<std::string, std::string> root;
  std::unordered_map<std::string, int> rank;

  std::string find(const std::string& email) {
    if (email == root[email]) return email;
    return root[email] = find(root[email]);
  }

  void connect(const std::string& x, const std::string& y) {
    auto root_x = find(x);
    auto root_y = find(y);

    if (root_x == root_y) return;

    if (rank[root_x] < rank[root_y]) {
      root[root_x] = root_y;
    } else if (rank[root_x] > rank[root_y]) {
      root[root_y] = root_x;
    } else {
      root[root_x] = root_y;
      rank[root_y]++;
    }
  }

 public:
  vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
    std::unordered_map<std::string, std::string> graph;  // <email, name>
    for (auto&& vec : accounts) {
      const auto& name = vec.front();
      for (size_t i = 1; i < vec.size(); ++i) {
        graph[vec[i]] = name;
        root[vec[i]] = vec[i];
        rank[vec[i]] = 0;
      }
    }

    for (auto&& vec : accounts) {
      const auto& email = vec[1];
      for (size_t i = 2; i < vec.size(); ++i) {
        connect(vec[i], email);
      }
    }

    for (auto&& vec : accounts) {
      for (size_t i = 1; i < vec.size(); ++i) {
        find(vec[i]);
      }
    }

    std::unordered_map<std::string, std::vector<std::string>> groups;
    for (auto&& [from, to] : root) {
      groups[to].push_back(from);
    }

    std::vector<std::vector<std::string>> vec;
    for (auto&& [to, froms] : groups) {
      std::sort(froms.begin(), froms.end());
      const auto& name = graph[to];
      vec.push_back({name});
      vec.back().insert(
        vec.back().end(), std::make_move_iterator(froms.begin()),
        std::make_move_iterator(froms.end())
      );
    }

    return vec;
  }
};
