#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  std::vector<std::vector<int>> graph;
  std::vector<std::vector<int>> cache;

 public:
  int shortestPathLength(vector<vector<int>>& __graph) {
    graph = std::move(__graph);
    return bfs();
  }

  int bfs() {
    int n = graph.size();
    if (n == 1) return 0;
    int ending = (1 << n) - 1;
    std::queue<std::pair<int, int>> queue;  // <node, mask>
    std::vector<std::vector<bool>> seen(n, std::vector<bool>(ending));

    for (int node = 0; node < n; ++node) {
      queue.emplace(node, 1 << node);
      seen[node][1 << node] = true;
    }

    int steps = 0;
    while (queue.size()) {
      const int size = queue.size();
      for (int i = 0; i < size; ++i) {
        auto [node, mask] = queue.front();
        queue.pop();

        for (int neighbor : graph[node]) {
          int next_mask = mask | (1 << neighbor);
          if (next_mask == ending) return 1 + steps;
          if (seen[neighbor][next_mask]) continue;
          seen[neighbor][next_mask] = true;
          queue.push({neighbor, next_mask});
        }
      }
      steps++;
    }

    return -1;
  }

  int dp_bfs() {
    int n = graph.size();
    int ending = (1 << n) - 1;
    cache.assign(n + 1, std::vector<int>(ending + 1));
    // backwards dp from neighbor to node
    // dp(node, mask) = 1 + min(             // start from popcount(mask) == n
    //    dp(neighbor, mask),                // visited
    //    dp(neighbor, mask ^ (1 << node))   // unvisited
    // ) for all neighbors of node
    // dp(node, mask) = 0 where popcount(mask) == 1  // ends at a base case
    int best = INT_MAX;
    for (int node = 0; node < n; ++node)
      best = std::min(best, dfs(node, ending));

    return best;
  }

  int dfs(int node, int mask) {
    if (cache[node][mask]) return cache[node][mask];  // visited
    if ((mask & (mask - 1)) == 0) return 0;  // base case; only 1 node visited

    cache[node][mask] = INT_MAX - 1;

    for (int neighbor : graph[node]) {
      if (mask & (1 << neighbor)) {  // from neighbor
        int visited = dfs(neighbor, mask);
        int unvisited = dfs(neighbor, mask ^ (1 << node));
        int better = std::min(visited, unvisited);
        cache[node][mask] = std::min(cache[node][mask], 1 + better);
      }
    }

    return cache[node][mask];
  }
};
