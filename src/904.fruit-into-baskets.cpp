#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int totalFruit(vector<int>& fruits) {
    int n = fruits.size();
    int max_len = 1;
    std::unordered_map<int, int> map;  // <type, count>

    for (int lo = 0, hi = 0; hi < n; ++hi) {
      map[fruits[hi]]++;

      while (map.size() > 2) {
        if (--map[fruits[lo]] == 0) map.erase(fruits[lo]);
        lo++;
      }

      max_len = std::max(max_len, hi - lo + 1);
    }

    return max_len;
  }
};
