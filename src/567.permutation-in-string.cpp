#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  bool checkInclusion(string& s1, string& s2) {
    // s1 =    "ab"
    // s2 = "eidbaooo"

    // sliding window of size s1.size()
    std::unordered_map<char, int> map1, map2;
    for (char ch : s1) map1[ch]++;

    auto check = [&]() {
      for (auto [ch, cnt] : map2) {
        auto it = map1.find(ch);
        if (it == map1.end()) return false;
        if (cnt > it->second) return false;
      }
      return true;
    };

    for (int lo = 0, hi = 0; hi < s2.size(); ++hi) {
      map2[s2[hi]]++;

      while (lo < hi && !check()) {
        map2[s2[lo]]--;
        if (map2[s2[lo]] == 0) map2.erase(s2[lo]);
        lo++;
      }
      if (map1 == map2) return true;
    }

    return false;
  }
};
