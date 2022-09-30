#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  inline bool is_pow2(int x) { return (x & (x - 1)) == 0; }

 public:
  int countPairs(vector<int>& arr) {
    int count = 0;
    const int mod = 1e9 + 7;
    std::unordered_map<int, int> map;
    for (int num : arr) {
      for (int i = 0; i < 22; ++i) {
        auto it = map.find((1 << i) - num);
        if (it != map.end()) {
          count += it->second;
          count %= mod;
        }
      }
      map[num]++;
    }

    return count;
  }
};
