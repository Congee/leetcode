#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int numSplits(string s) {
    // scan once to record a map of the count of each character
    // scan again to plus on left and minus count of each character on right
    std::array<int, 26> left = {}, right = {};
    int count = 0;

    auto check = [&]() {
      int left_distinct = 0, right_distinct = 0;
      for (int cnt : left) left_distinct += cnt != 0;
      for (int cnt : right) right_distinct += cnt != 0;
      return left_distinct == right_distinct;
    };
    for (char ch : s) right[ch - 'a']++;
    for (char ch : s) {
      left[ch - 'a']++;
      right[ch - 'a']--;
      // this can be optimized out by maintaining counts of distinct characters
      // on both sides;
      count += check();
    }

    return count;
  }
};
