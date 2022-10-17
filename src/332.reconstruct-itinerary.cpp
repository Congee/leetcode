#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  std::unordered_map<std::string, std::vector<std::string>> adj;
  std::vector<std::string> stack;
  std::unordered_map<std::string, int> tickets_rec;
  vector<vector<string>> tickets;
  size_t used_cnt;
  size_t n;

 public:
  // can we use topological sort?
  vector<string> findItinerary(vector<vector<string>>& __tickets) {
    tickets = std::move(__tickets);
    n = tickets.size();
    for (auto&& v : tickets) {
      auto& from = v[0];
      auto& to = v[1];
      adj[from].push_back(to);
      tickets_rec[from + to]++;
    };

    eulerian();
    return stack;

    return by_backtrack();
  }

  std::vector<std::string> eulerian() {
    std::unordered_map<std::string, std::list<std::string>> adj;
    for (auto&& [k, vec] : this->adj) {
      std::sort(vec.begin(), vec.end());
      adj[k].assign(vec.begin(), vec.end());
    };

    dfs("JFK", adj);

    std::reverse(stack.begin(), stack.end());
    return stack;
  }

  void dfs(
    const std::string& start,
    std::unordered_map<std::string, std::list<std::string>>& foo
  ) {
    auto& curr = foo[start];
    while (curr.size()) {
      auto nb = curr.front();
      curr.pop_front();
      dfs(nb, foo);
    }
    stack.push_back(start);
  }

  vector<string> by_backtrack() {
    used_cnt = 0;

    // XXX: greed is good
    for (auto&& [_, cities] : adj) std::sort(cities.begin(), cities.end());

    stack.push_back("JFK");
    backtrack("JFK");

    return stack;
  }

  bool backtrack(const std::string& start) {
    if (used_cnt == n) return true;

    for (auto&& nb : adj[start]) {
      auto joined = start + nb;
      if (tickets_rec[joined] == 0) continue;

      stack.push_back(nb);
      tickets_rec[joined]--;
      used_cnt++;

      if (backtrack(nb)) return true;

      stack.pop_back();
      tickets_rec[joined]++;
      used_cnt--;
    }

    return false;
  }
};
