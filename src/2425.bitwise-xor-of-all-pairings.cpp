#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int xorAllNums(vector<int>& nums1, vector<int>& nums2) {
    // odd odd
    // {a,b,c}
    // {d,e,f}
    // ad ae af, bd be bf, cd ce cf
    // each char appears 3 times, so result is {a^b^c} ^ {d^e^f}
    //
    // odd even
    // {a,b,c}
    // {d,e}
    // ad ae, bd be, cd ce
    // each char in {abc} appears 2 times, each char in {de} appears 3 times
    // so, result is {d^e}

    int x = 0, y = 0;
    for (int a : nums1) x ^= a;
    for (int b : nums2) y ^= b;
    return (nums1.size() % 2 * y) ^ (nums2.size() % 2 * x);
  }

  int tle(vector<int>& nums1, vector<int>& nums2) {
    std::unordered_map<int, int> map1;  // <num, count>
    std::unordered_map<int, int> map2;  // <num, count>
    for (auto x : nums1) {
      if (++map1[x] == 2) map1.erase(x);
    }
    for (auto x : nums2) {
      if (++map2[x] == 2) map2.erase(x);
    }

    int base = 0;
    for (auto [n1, _] : map1) {
      for (auto [n2, _] : map2) {
        base ^= n1 ^ n2;
      }
    }

    return base;
  }
};
