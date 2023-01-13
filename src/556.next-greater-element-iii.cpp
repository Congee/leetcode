#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int nextGreaterElement(int n) {
    // 54321 => -1
    // 12345 => 12354
    // 12321 => 13122
    if (n < 10 || n == INT_MAX) return -1;
    auto str = std::to_string(n);
    int hi = str.size() - 2, lo = str.size() - 1;

    while (hi >= 0 && str[hi] >= str[hi + 1]) hi--;
    if (hi >= 0) {
      while (str[lo] <= str[hi]) lo--;
      std::swap(str[lo], str[hi]);
      std::reverse(str.begin() + hi + 1, str.end());
      long num = std::stol(str);
      return num > INT_MAX ? -1 : num;
    }

    return -1;
  }
};
