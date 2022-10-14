#ifdef __LOCAL__
#include <leetcode.h>
#endif

using Pair = std::pair<double, int>;

class Solution {
  std::vector<std::vector<Pair>> adj;  // <from, [prob, to]>
 public:
  double maxProbability(
    int n,
    vector<vector<int>>& edges,
    vector<double>& succProb,
    int start,
    int end
  ) {
    adj.resize(n);
    for (size_t i = 0; i < edges.size(); ++i) {
      auto from = edges[i][0];
      auto to = edges[i][1];
      auto prob = succProb[i];
      adj[from].push_back({prob, to});
      adj[to].push_back({prob, from});
    }

    return spfa(n, start, end);
    return bellman_ford(n, start, end);
    return dijkstra(n, start, end);
  }

  double bellman_ford(int n, int start, int end) {
    // dp[n][v] = min([dp[n - 1][u] + dist(u, v) | u <- adj[v].froms])
    //
    // Start by constructing a table of (num_edges - 1) * (num_vertices]).
    // Iterate the table and update the current row from the previous row based
    // on the distance from each neighbor of the previous row.
    //
    // This is dynamic programming. As the current row depends on the prev row.
    //
    // Optimization 1: keep only two rows prev and curr to save space.
    // Optimization 2: stop updating if we've updated nothing. I.e., after
    // updating, still curr == prev
    //
    // use version 1 if we want at most k edges
    // use version 2 if we want the shortest distance between A and B
    //
    // To detect "negative weight cycles"
    // perform an extra Nth relaxation.
    // distances[u] + weight(u, v) < distances[v] + edge(u, v)

    std::vector<double> prev(n, 0);
    prev[start] = 1;
    auto curr = prev;
    for (int i = 0; i < n - 1; ++i) {
      bool keepgoing = false;
      for (int j = 0; j < n; ++j) {
        for (auto&& [prob, from] : adj[j]) {
          auto prod = prev[from] * prob;
          if (prod > curr[j]) {
            curr[j] = prod;
            keepgoing = true;
          }
        }
      }
      if (keepgoing == false) break;
      prev = curr;
    }

    return curr[end];
  }

  double spfa(int n, int start, int end) {
    std::vector<double> probs(n, 0);
    probs[start] = 1;

    // adapted from the bellman ford algorithm
    // core idea: retry each updated neighbor until it cannot be updated
    std::queue<int> queue;  // <vertex>
    queue.push(start);

    while (queue.size()) {
      auto curr = queue.front();
      queue.pop();

      for (auto&& [prob, to] : adj[curr]) {
        auto prod = prob * probs[curr];
        if (prod > probs[to]) {
          probs[to] = prod;
          queue.push(to);
        }
      }
    }

    return probs[end];
  }

  double dijkstra(int n, int start, int end) {
    std::vector<Pair> table(n, {0, -1});  // <curr, [prob, from]>
    table[start] = {1, -1};

    // greedy. the next next we will pop is always optimal at this point
    std::priority_queue<Pair, std::vector<Pair>, std::less<Pair>> pq;
    pq.emplace(1, start);

    while (pq.size()) {
      auto [acc, curr] = pq.top();
      pq.pop();

      if (curr == end) return acc;

      for (auto&& [to_prob, to] : adj[curr]) {
        auto prod = to_prob * acc;
        if (table[to].first < prod) {
          table[to] = {prod, curr};
          pq.emplace(prod, to);
        }
      }
    }

    return 0;
  }
};
