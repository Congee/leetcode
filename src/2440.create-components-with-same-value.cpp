#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  vector<int> nums;
  vector<vector<int>> edges;
  std::vector<std::vector<int>> adj;
  int n;

 public:
  int componentValue(vector<int>& __nums, vector<vector<int>>& __edges) {
    nums = std::move(__nums);
    edges = std::move(__edges);
    n = nums.size();
    int sum = std::accumulate(nums.begin(), nums.end(), 0);

    adj.resize(n);
    for (auto&& e : edges) {
      auto from = e[0];
      auto to = e[1];
      adj[from].push_back(to);
      adj[to].push_back(from);
    }

    // for a evenly distributed tree, the sum of each component shall be able
    // to divide `sum`
    for (int comps = n; comps >= 1; --comps) {
      if (!(sum % comps) && dfs(0, sum / comps) == 0) return comps - 1;
    }

    return 0;
  }

  //      (0) 6
  //      .
  //      .
  //      (1) 2
  //     /   \
  //  2(2)  2(3) ... (4) 6
  int dfs(int node, int each, int parent = -1) {
    // sum of current node and dfs(curr)
    // if sum == each return 0
    // otherwise return sum
    int total = nums[node];
    for (int kid : adj[node]) {
      if (kid == parent) continue;

      int rem = dfs(kid, each, node);
      if (rem < 0) return -1;
      total += rem;
    }

    if (total == each) return 0;
    if (total > each) return -1;

    return total;
  }
};
