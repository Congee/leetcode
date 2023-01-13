#ifdef __LOCAL__
#include <leetcode.h>
#endif

const int mod = 1e9 + 7;

class Solution {
 public:
  int rectangleArea(vector<vector<int>>& rectangles) {
    //    |
    // ---+--
    // ---+---
    //    |

    // two dimensional sweep line
    // on encoutering each vertical line, loop horizontal lines to get the area

    std::vector<std::array<int, 4>> vlines;  // <x, type, hlo, hhi>
    for (auto&& rect : rectangles) {
      int x = rect[0], y = rect[1], a = rect[2], b = rect[3];

      vlines.push_back({x, -1, y, b});
      vlines.push_back({a, +1, y, b});
    }
    std::sort(vlines.begin(), vlines.end());
    std::multiset<std::pair<int, int>> hlines;

    // 1D sweep line upwards
    auto get_area = [&](const int x) -> long long {
      long long area = 0, count = 0, prev = INT_MAX;
      for (auto&& [row, type] : hlines) {
        count += type;
        if (count == type) prev = row;
        if (count == 0) area = (area + (row - prev) * x % mod) % mod;
      }
      return area;
    };

    long long area = 0, prev = INT_MAX;
    for (auto&& vline : vlines) {
      auto&& [x, type, hlo, hhi] = vline;

      if (type != INT_MAX) area = (area + get_area(x - prev)) % mod;

      if (type < 0) {
        hlines.insert({hlo, -1});  // entry
        hlines.insert({hhi, +1});  // exit
      } else {
        hlines.erase(hlines.find({hlo, -1}));
        hlines.erase(hlines.find({hhi, +1}));
      }

      prev = x;
    }

    return area;
  }
};
