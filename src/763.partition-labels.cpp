#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  vector<int> partitionLabels(string& s) {
    return greedy(s);
    return sweep_line(s);
  }

  vector<int> greedy(string& s) {
    // for each character, process the last occurrence of that letter, extending
    // the current partition
    int n = s.size();
    std::array<int, 26> map = {};
    for (int i = 0; i < n; ++i) map[s[i] - 'a'] = i;

    std::vector<int> vec;
    for (int lo = 0, hi = 0, stop = 0; hi < n; ++hi) {
      stop = std::max(stop, map[s[hi] - 'a']);
      if (stop == hi) {  // meeting the last occurence
        vec.push_back(hi - lo + 1);
        lo = hi + 1;
      }
    }

    return vec;
  }

  vector<int> sweep_line(string& s) {
    // ababcbaca|defegd|ehijhklij
    // |ababcbaca|d|efegde|hijhklij
    // record the first and last appearance of each character
    // insert these indices into a treeset
    // merge if there's an overlap
    std::vector<std::pair<int, int>> records(26, {INT_MAX, 0});
    int n = s.size();

    for (int i = 0; i < n; ++i) {
      char ch = s[i] - 'a';
      auto& ref = records[ch];
      ref.first = std::min(ref.first, i);
      ref.second = std::max(ref.second, i);
    }

    std::vector<std::pair<int, int>> lines;
    for (char ch = 0; ch < 26; ++ch) {
      auto&& [lo, hi] = records[ch];
      if (lo == INT_MAX) continue;

      lines.push_back({lo + 0, +1});
      lines.push_back({hi + 1, -1});
      // ----
      //      ----
      //
      // -----
      //   --
      //
      //     ----
      // ----
    }
    std::sort(lines.begin(), lines.end());

    std::vector<int> vec;
    int matched = 0, started = false;
    for (auto&& [pos, type] : lines) {
      matched += type;

      if (matched == 1 && !started) {
        vec.push_back(pos);
        started = true;
      }
      if (matched == 0) {
        vec.back() = pos - vec.back();
        started = false;
      }
    }

    return vec;
  }
};
