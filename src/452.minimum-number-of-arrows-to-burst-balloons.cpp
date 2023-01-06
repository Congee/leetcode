#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int findMinArrowShots(vector<vector<int>>& points) {
    //                      -----
    //                      -----
    //                      -----
    // -------      -------------
    //     -------------
    // 1   2    1   2          4

    // --
    //  --
    //   --
    //    --

    return greedy(points);
  }

  int greedy(vector<vector<int>>& points) {
    std::sort(
      points.begin(),
      points.end(),
      [&](const auto& lhs, const auto& rhs) { return lhs[1] < rhs[1]; }
    );

    // every balloon must burst

    long count = 0, end = LONG_MIN;
    for (auto&& p : points) {
      if (end >= p[0]) continue;

      count++;
      end = p[1];
    }

    return count;
  }
};
