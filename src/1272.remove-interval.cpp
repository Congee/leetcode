#ifdef __LOCAL__
#include <leetcode.h>
#endif

using vv = vector<vector<int>>;

class Solution {
 public:
  vv removeInterval(vv& intervals, vector<int>& toBeRemoved) {
    return by_prev(intervals, toBeRemoved);
    return sweep_treemap(intervals, toBeRemoved);
  }

  vv by_prev(vv& intervals, vector<int>& toBeRemoved) {
    vv vec;
    for (auto&& interval : intervals) {
      int left = interval[0], right = interval[1];

      if (right < toBeRemoved[0] || left > toBeRemoved[1])
        vec.push_back(interval);
      else {
        if (left < toBeRemoved[0]) vec.push_back({left, toBeRemoved[0]});
        if (right > toBeRemoved[1]) vec.push_back({toBeRemoved[1], right});
      }
    }
    return vec;
  }

  vv greedy(vv& intervals, vector<int>& toBeRemoved) {
    int lo = toBeRemoved[0], hi = toBeRemoved[1];
    vv vec;
    for (auto&& interval : intervals) {
      int left = interval[0], right = interval[1];
      if (std::min(right, lo) > left)
        vec.push_back({interval[0], std::min(right, lo)});
      if (std::max(left, hi) < right)
        vec.push_back({std::max(left, hi), interval[1]});
    }

    return vec;
  }

  vv sweep_treemap(vv& intervals, vector<int>& toBeRemoved) {
    std::map<int, int> tree;  // <pos, type>
    for (auto&& interval : intervals) {
      tree[interval[0]]++;
      tree[interval[1]]--;
    }

    tree[toBeRemoved[0]]--;
    tree[toBeRemoved[1]]++;

    vv vec;
    int count = 0;
    bool added = false;
    for (auto&& [pos, type] : tree) {
      count += type;

      if (count == 1 && type == 1) {
        vec.push_back({pos, -1});
        added = true;
      }

      if (count == 0 && added) {
        vec.back().back() = pos;
        added = false;
      }
    }
    return vec;
  }

  vv ugly_sweep(vv& intervals, vector<int>& toBeRemoved) {
    std::vector<std::pair<int, int>> lines;  // <pos, type>
    for (auto&& interval : intervals) {
      lines.push_back({interval[0], -1});
      lines.push_back({interval[1], +1});
    }
    lines.push_back({toBeRemoved[0], -2});
    lines.push_back({toBeRemoved[1], +2});
    std::sort(lines.begin(), lines.end());

    bool removing = false;
    int matched = 0;
    vv vec;
    for (auto&& [pos, type] : lines) {
      if (type == -2) removing = true;
      if (type == +2) removing = false;

      if (std::abs(type) == 1) matched += type;

      if (std::abs(type) == 1 && (pos == toBeRemoved[0] || pos == toBeRemoved[1]))
        continue;

      if (0)
        ;
      else if (matched == -1 && !removing)
        vec.push_back({pos, -1});

      else if (matched == -1 && removing && pos == toBeRemoved[0])
        vec.back().back() = pos;

      else if (matched == -1 && removing)
        continue;

      else if (matched == +0 && removing)
        continue;

      else if (matched == +0 && !removing && pos == toBeRemoved[1])
        continue;

      else if (matched == +0 && !removing)
        vec.back().back() = pos;
    }

    return vec;
  }
};
