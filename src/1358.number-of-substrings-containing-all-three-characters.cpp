#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int numberOfSubstrings(const std::string& s) { return genius(s); }

  int genius(const std::string& s) {
    int last[] = {-1, -1, -1}, count = 0, n = s.size();
    for (int i = 0; i < n; ++i) {
      last[s[i] - 'a'] = i;
      count += 1 + std::min({last[0], last[1], last[2]});
    }
    return count;
  }

  int regular(const std::string& s) {
    // aaacb
    int count = 0, map[] = {0, 0, 0};

    for (size_t lo = 0, hi = 0; hi < s.size(); ++hi) {
      map[s[hi] - 'a']++;

      while (map[0] > 0 && map[1] > 0 && map[2] > 0) --map[s[lo++] - 'a'];

      count += lo;
    }

    return count;
  }

  int tle(const std::string& s) {
    // aaacb
    int count = 0, map[] = {0, 0, 0};

    for (size_t lo = 0, hi = 0; hi < s.size(); ++hi) {
      map[s[hi] - 'a']++;

      auto mmm = map;
      auto x = lo;
      while (mmm[0] > 0 && mmm[1] > 0 && mmm[2] > 0) {
        mmm[s[x] - 'a']--;
        x++;
        count++;
      }
    }

    return count;
  }
};
