#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  bool carPooling(vector<vector<int>>& trips, int capacity) {
    // abstraction: max number of overlapping intervals
    // ---------------
    //   --
    //    --
    //       -----
    //        --
    //         ---
    //         # = 4 here

    return line_sweep(trips, capacity);
  }

  bool line_sweep(vector<vector<int>>& trips, int capacity) {
    std::vector<std::pair<int, int>> boundaries;  // <pos, passengers>

    for (auto&& trip : trips) {
      boundaries.emplace_back(trip[1], +trip[0]);
      boundaries.emplace_back(trip[2], -trip[0]);  // drop off then pick up
    }

    std::sort(boundaries.begin(), boundaries.end());

    int passengers = 0;
    for (auto&& [pos, type] : boundaries) {
      passengers += type;
      if (passengers > capacity) return false;
    }

    return true;
  }
};
