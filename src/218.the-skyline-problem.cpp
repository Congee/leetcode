#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
    // +------+
    // |      |
    // +------+
    // |      |
    // |      |
    //
    //
    // +------+
    // |      |
    // +--+   |
    // |  |   |
    // |  |   |
    //
    // +--+
    // |  |
    // +--+---+
    // |  |   |
    // |  |   |
    //
    //
    // +--+---+
    // |  |   |
    // |  |   |
    using Line = std::tuple<int, int, int>;  // <pos, type, height>

    std::priority_queue<Line, std::vector<Line>, std::greater<Line>> lines;
    for (auto&& building : buildings) {
      lines.push({building[0], -1, building[2]});
      lines.push({building[1], +1, building[2]});
    }

    std::vector<std::vector<int>> vec;
    std::multiset<int> tree;  // <height>
    while (lines.size()) {
      int before = tree.size() ? *tree.rbegin() : 0;

      // put all overlapped sweep line together
      int curr_pos;
      do {
        auto [pos, type, height] = lines.top();
        curr_pos = pos;
        lines.pop();

        type == -1 ? tree.insert(height) : tree.erase(tree.find(height));
      } while (lines.size() && std::get<0>(lines.top()) == curr_pos);

      int after = tree.size() ? *tree.rbegin() : 0;

      if (before != after) vec.push_back({curr_pos, after});
    }

    return vec;
  }
};
