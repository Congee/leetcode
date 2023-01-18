#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int minSteps(string& s, string& t) {
    // take hashmap<char, count> of both
    // count total number of differences
    // return n - count;

    int n = s.size();
    std::unordered_map<char, int> smap, tmap;
    for (int i = 0; i < n; ++i) {
      smap[s[i]]++;
      tmap[t[i]]++;
    }

    int count = n;
    for (int i = 0; i < 26; ++i) {
      char ch = i + 'a';
      count -= std::min(smap[ch], tmap[ch]);
    }

    return count;
  }
};
