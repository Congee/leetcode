#ifdef __LOCAL__
#include <leetcode.h>
#endif

using Pair = std::pair<int, int>;
using Item = std::pair<int, Pair>;

class Solution {
 public:
  int isRectangleCover(vector<vector<int>>& rectangles) {
    return sweep_line(rectangles);
    return math(rectangles);
  }

  int sweep_line(vector<vector<int>>& rectangles) {
    // 1. traverse columns of each rectangle ascendingly
    // 2. maintain columns of each rectangle in a tree set
    // 3. if there's an overlap between columns, return false
    // 4. finally check the largest area for integrity
    int minx = INT_MAX, miny = INT_MAX, maxa = INT_MIN, maxb = INT_MIN;
    long area = 0;
    std::priority_queue<Item, std::vector<Item>, std::greater<Item>> pq;
    for (auto&& rect : rectangles) {
      int x = rect[0], y = rect[1], a = rect[2], b = rect[3];
      pq.push({x * 2 + 1, {y, b}});
      pq.push({a * 2 + 0, {y, b}});

      minx = std::min(minx, x);
      miny = std::min(miny, y);
      maxa = std::max(maxa, a);
      maxb = std::max(maxb, b);
      area += (long)(a - x) * (b - y);
    }

    std::set<Pair> tree;
    while (pq.size()) {
      auto [x, col] = pq.top();

      if (x & 1) {  // left x
        auto it = tree.lower_bound(col);
        if (it != tree.begin() && std::prev(it)->second > col.first)
          return false;
        if (it != tree.end() && it->first < col.second) return false;
        tree.insert(col);
      } else {  // right a
        tree.erase(col);
      }

      pq.pop();
    }

    return area == (long)(maxa - minx) * (maxb - miny);
  }

  int math(vector<vector<int>>& rectangles) {
    // obvservations:
    // 1. the area of the largest rectangle = sum of all sub rectangles
    // 2. new points cancel old points. finally only the 4 corner points remain

    std::unordered_map<long, int> map;  // <point, count>
    for (auto&& rect : rectangles) {
      int x = rect[0], y = rect[1], a = rect[2], b = rect[3];
      const long mul = 1e6;
      ++map[x * mul + y];
      ++map[a * mul + b];
      --map[x * mul + b];
      --map[a * mul + y];
    }

    int count = 0;
    for (auto&& [_, cnt] : map) count += std::abs(cnt);
    return count == 4;
  }
};
