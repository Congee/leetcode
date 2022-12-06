#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    std::sort(
      intervals.begin(),
      intervals.end(),
      [&](const auto& lhs, const auto& rhs) { return lhs[0] < rhs[0]; }
    );

    // --
    //  ---
    //
    //  -----
    //    --
    //      -
    //
    //  ----
    //     ---
    //       ---
    //
    //
    //  -
    //  -
    //  -
    //
    //
    // dp(n) = min of
    //       = 0 + dp(n+1)
    //       = 1 + dp(n+1) if overlap(n, n+1)

    // greedy
    int count = 0;
    auto& end = intervals[0][1];
    for (int i = 1; i < intervals.size(); ++i) {
      auto& curr = intervals[i];
      if (end > curr[0]) {
        end = std::min(end, curr[1]);
        count++;
      } else {
        end = curr[1];
      }
    }
    return count;
  }
};
