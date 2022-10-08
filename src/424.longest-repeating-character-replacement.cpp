#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int characterReplacement(const string& s, int k) { return optimal(s, k); }

  int optimal(const string& s, int k) {
    int n = s.size(), lo = 0;
    std::array<int, 26> count = {};
    int maxf = 0;
    for (int hi = lo; hi < n; ++hi) {
      maxf = std::max(maxf, ++count[s[hi] - 'A']);
      if (hi - lo + 1 > maxf + k) --count[s[lo++] - 'A'];
    }
    return n - lo;
  }

  int naive(const string& s, int k) {
    // AABABBA
    //    B

    std::unordered_map<char, int> map;  // <char, count>
    int max_len = 1;
    int n = s.size();
    int curr_len = 0;
    int most_ch = s[0];
    for (int lo = 0, hi = 0; hi < n; ++hi) {
      map[s[hi]]++;
      curr_len++;

      if (map[s[hi]] > most_ch) most_ch = s[hi];

      // BBBBAAA, k=3
      // XBBBBAAA, k=3
      while (curr_len - map[most_ch] > k) {
        if (--map[s[lo]] == 0) map.erase(s[lo]);
        curr_len--;

        if (s[lo] == most_ch) {  // k = 0?
          auto it = std::max_element(
            map.begin(),
            map.end(),
            [&](const auto& lhs, const auto& rhs) {
              return lhs.second < rhs.second;
            }
          );
          most_ch = it->first;
        }

        lo++;
      }

      max_len = std::max(max_len, hi - lo + 1);
    }

    return max_len;
  }
};
