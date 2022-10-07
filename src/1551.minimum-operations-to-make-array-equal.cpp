#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int minOperations(int n) {
    if (n & 1) {
      // n = 5
      // 1 3 5 7 9
      // 4+2+0
      return (n / 2 + 1) * (0 + n - 1) / 2;
    } else {
      // n = 6
      // 1 3 5 7 9 11
      // 5+3+1
      return (n / 2) * (1 + n - 1) / 2;
    }
  }
};
