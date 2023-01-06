#ifdef __LOCAL__
#include <leetcode.h>
#endif

using vv = vector<vector<int>>;

class Solution {
 public:
  vv insert(vv& intervals, vector<int>& newInterval) {
    return sweep(intervals, newInterval);
    return stupid_naive(intervals, newInterval);
  }

  vv sweep(vv& intervals, vector<int>& newInterval) {
    std::vector<std::pair<int, int>> lines;  // <pos, type>

    for (auto&& interval : intervals) {
      lines.push_back({interval[0], -1});
      lines.push_back({interval[1], +1});
    }

    lines.push_back({newInterval[0], -1});
    lines.push_back({newInterval[1], +1});

    std::sort(lines.begin(), lines.end());

    vv vec;
    int count = 0, left = INT_MIN;
    bool is_open = false;
    for (auto&& [pos, type] : lines) {
      count += type;

      if (!is_open) {
        left = pos;
        is_open = true;
      }

      if (count == 0) {
        vec.push_back({left, pos});
        is_open = false;
      }
    }

    return vec;
  }

  vv stupid_naive(vv& intervals, vector<int>& newInterval) {
    if (intervals.empty()) return {newInterval};

    vv vec;
    if (newInterval[1] < intervals.front().front()) {
      vec.push_back(newInterval);
      vec.insert(vec.end(), intervals.begin(), intervals.end());
      return vec;
    }

    if (newInterval[0] > intervals.back().back()) {
      vec = intervals;
      vec.push_back(newInterval);
      return vec;
    }

    if (newInterval[0] <= intervals[0][0] && intervals.back().back() <= newInterval[1])
      return {newInterval};

    //   -------
    // ---
    //
    //   -------
    //     ---
    //
    //   -------
    //        ---
    //
    //        ---
    //   -------------

    bool started = false;
    for (auto&& interval : intervals) {
      int lo = interval[0], hi = interval[1];

      // outside
      if (hi < newInterval[0] || lo > newInterval[1]) {
        if (!started && lo > newInterval[1]) {
          vec.push_back(newInterval);
          started = true;
        }
        vec.push_back(interval);
      }

      // inside
      else if (newInterval[0] <= lo && hi <= newInterval[1]) {
        if (!started) {
          vec.push_back(
            {std::min(lo, newInterval[0]), std::max(newInterval[1], hi)}
          );
          started = true;
        }
      }

      // overlap
      else if (hi >= newInterval[0]) {
        if (started) {
          vec.back().back() = std::max(newInterval[1], hi);
        } else {
          vec.push_back(
            {std::min(lo, newInterval[0]), std::max(newInterval[1], hi)}
          );
          started = true;
        }
      }
    }

    if (newInterval[1] > vec.back().back()) vec.back().back() = newInterval[1];

    return vec;
  }
};
