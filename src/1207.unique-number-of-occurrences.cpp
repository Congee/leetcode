#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  bool uniqueOccurrences(vector<int>& arr) { return naive(arr); }

  bool naive(vector<int>& arr) {
    std::unordered_map<int, int> map;  // <num, count>
    for (auto num : arr) map[num]++;
    std::unordered_set<int> seen;
    for (auto&& [_, cnt] : map) {
      if (seen.count(cnt)) return false;
      seen.insert(cnt);
    }

    return true;
  }
};
