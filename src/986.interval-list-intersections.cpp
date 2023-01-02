#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  vector<vector<int>> intervalIntersection(
    vector<vector<int>>& firstList, vector<vector<int>>& secondList
  ) {
    return two_pointers(firstList, secondList);
    return line_sweep(firstList, secondList);
  }

  vector<vector<int>> two_pointers(
    vector<vector<int>>& firstList, vector<vector<int>>& secondList
  ) const {
    int n = firstList.size(), m = secondList.size(), fst = 0, snd = 0;
    if (n == 0 || m == 0) return {};

    vector<vector<int>> vec;
    while (fst < n && snd < m) {
      int lo = std::max(firstList[fst][0], secondList[snd][0]);
      int hi = std::min(firstList[fst][1], secondList[snd][1]);
      if (lo <= hi) vec.push_back({lo, hi});

      if (firstList[fst][1] < secondList[snd][1])
        fst++;
      else
        snd++;
    }
    return vec;
  }

  vector<vector<int>> line_sweep(
    vector<vector<int>>& firstList, vector<vector<int>>& secondList
  ) {
    // two lists are strictly increasing, do like in mergge sort then
    int n = firstList.size(), m = secondList.size();
    if (n == 0 || m == 0) return {};

    std::vector<std::pair<int, int>> boundaries;  // <pos, type>
    for (auto&& v : firstList) {
      boundaries.emplace_back(v[0], +1);
      boundaries.emplace_back(v[1], -1);
    }

    for (auto&& v : secondList) {
      boundaries.emplace_back(v[0], +1);
      boundaries.emplace_back(v[1], -1);
    }

    std::sort(boundaries.begin(), boundaries.end());

    vector<vector<int>> vec;
    int match = 0, prev_match = INT_MIN, prev_pos = INT_MIN;
    for (auto&& [pos, type] : boundaries) {
      match += type;
      if (match == 0) {
      } else if (match == 2) {
        vec.push_back({pos, INT_MIN});
      } else if (match == 1 && prev_match == 2) {
        vec.back().back() = pos;
      } else if (match == 1 && prev_pos == pos) {
        vec.push_back({pos, pos});
      }
      prev_match = match;
      prev_pos = pos;
    }
    return vec;
  }
};
