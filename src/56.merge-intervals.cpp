#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  vector<vector<int>> merge(vector<vector<int>>& intervals) {
    return line_sweep(intervals);
    return greedy(intervals);
  }

  vector<vector<int>> greedy(vector<vector<int>>& intervals) {
    int n = intervals.size();
    if (n == 1) return intervals;

    std::sort(
      intervals.begin(),
      intervals.end(),
      [&](const auto& lhs, const auto& rhs) { return lhs[0] < rhs[0]; }
    );

    std::vector<std::vector<int>> vec;
    vec.push_back(intervals[0]);
    for (int i = 1; i < n; ++i) {
      if (intervals[i][0] <= vec.back()[1]) {
        vec.back()[1] = std::max(vec.back()[1], intervals[i][1]);
      } else {
        vec.push_back(intervals[i]);
      }
    }

    return vec;
  }

  vector<vector<int>> line_sweep(vector<vector<int>>& intervals) {
    // struct Boundary {
    //   int pos;
    //   int type;
    // };
    using Boundary = std::pair<int, int>;

    std::vector<Boundary> boundaries;
    for (auto&& interval : intervals) {
      boundaries.push_back({interval[0], -1});
      boundaries.push_back({interval[1], +1});
    }
    std::sort(boundaries.begin(), boundaries.end());

    vector<vector<int>> vec;
    int matched = 0, left = 0, right = 0;
    for (auto&& b : boundaries) {
      if (matched == 0) {
        left = b.first;
      }

      matched += b.second;
      if (matched == 0) {
        right = b.first;
        vec.push_back({left, right});
      }
    }

    return vec;
  }
};
