#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int balancedString(const string& s) {
    int n = s.size();
    std::unordered_map<char, int> map({{'Q', 0}, {'W', 0}, {'E', 0}, {'R', 0}});
    for (char ch : s) map[ch]++;

    // E 1      Q 1
    // R 2      W 2
    //          E 4
    //          R 5
    // (1 + 2 + 4 + 5) / 4 = 12 / 3 = 3
    // E: 4 - 3 = 1
    // R: 5 - 3 = 2
    // find the shortest subarry containing {R: 2, E 1}

    int mean = (map['Q'] + map['W'] + map['E'] + map['R']) / 4;
    std::unordered_map<char, int> target;
    if (map['Q'] > mean) target['Q'] = map['Q'] - mean;
    if (map['W'] > mean) target['W'] = map['W'] - mean;
    if (map['E'] > mean) target['E'] = map['E'] - mean;
    if (map['R'] > mean) target['R'] = map['R'] - mean;
    if (target.empty()) return 0;

    int shortest_len = n;
    std::unordered_map<char, int> window;
    for (int lo = 0, hi = 0; hi < n; ++hi) {
      window[s[hi]]++;

      while (ge(window, target)) {
        shortest_len = std::min(shortest_len, hi - lo + 1);
        window[s[lo++]]--;
      }
    }

    return shortest_len;
  }

  bool ge(
    std::unordered_map<char, int>& lhs, std::unordered_map<char, int>& rhs
  ) {
    if (lhs.size() < rhs.size()) return false;
    for (auto&& [ch, cnt] : rhs)
      if (lhs[ch] < cnt) return false;
    return true;
  }
};
