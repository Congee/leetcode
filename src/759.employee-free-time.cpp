#ifdef __LOCAL__
#include <leetcode.h>
#endif

#if 1
// Definition for an Interval.
class Interval {
 public:
  int start;
  int end;

  Interval() {}

  Interval(int _start, int _end) {
    start = _start;
    end = _end;
  }
};
#endif

class Solution {
 public:
  vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
    //
    //   ----
    // ----  ||||------

    std::vector<std::pair<int, int>> boundaries;  // <pos, type>

    for (auto&& employee : schedule) {
      for (auto&& interval : employee) {
        boundaries.emplace_back(interval.start, -1);
        boundaries.emplace_back(interval.end, 1);
      }
    }

    std::sort(boundaries.begin(), boundaries.end());

    std::vector<Interval> vec;
    int matched = 0;
    for (auto&& [pos, type] : boundaries) {
      if (matched == 0 && vec.size()) vec.back().end = pos;

      matched += type;

      if (matched == 0) vec.push_back(Interval(pos, -1));
    }

    if (vec.size() && vec.back().start == boundaries.back().first)
      vec.pop_back();

    return vec;
  }
};
