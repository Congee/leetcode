#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int twoCitySchedCost(vector<vector<int>>& costs) {
    return intuitive(costs);
    return greedy(costs);
  }

  int intuitive(vector<vector<int>>& costs) {
    int n = costs.size() / 2, sum = 0;
    std::vector<int> diffs;  // save as much as possible
    diffs.reserve(n);

    for (auto&& vec : costs) {
      sum += vec[0];
      diffs.push_back(vec[1] - vec[0]);
    }

    std::sort(diffs.begin(), diffs.end());
    for (int i = 0; i < n; ++i) sum += diffs[i];

    return sum;
  }

  int greedy(vector<vector<int>>& costs) {
    // greedy
    // sort by opportunity cost
    // always make up with the lowest cost

    std::nth_element(  // quickselect
      costs.begin(),
      costs.begin() + costs.size() / 2,
      costs.end(),
      [&](const auto& lhs, const auto& rhs) {
        return lhs[0] - lhs[1] < rhs[0] - rhs[1];
      }
    );

    int n = costs.size() / 2, sum = 0;
    for (int i = 0; i < n; ++i) sum += costs[i][0] + costs[i + n][1];
    return sum;
  }
};
