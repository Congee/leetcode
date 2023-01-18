#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int minFlipsMonoIncr(string s) { return dynamic_programming(s); }

  int dynamic_programming(string s) {
    // We know DP always maintain a valid construct when traversing.
    // Let us maintain a monotonically increasing subarray till curr pos.
    // When curr is 1, do nothing
    // When curr is 0, flip all 1s on the left, or flip curr 0 to 1
    // 011010010
    //    ^
    int dp = 0, ones = 0;
    for (char ch : s) ch == '0' ? dp = std::min(dp + 1, ones) : ones++;

    return dp;
  }
  int regular(string s) {
    // cannot do 1D dp because the current state does not exclusively depend on
    // prev state
    //
    // in other words, no 1 shall appear before 0
    //
    // I got stuck here;
    //
    // wasn't able to go one step further to and a cut | between all left zeros
    // and all right 1s
    //
    // We just need to count number of 1s on left and right of the cut |
    // 0010000|10  -> 2
    // 00000|1111
    //
    int n = s.size();
    std::vector<int> ones(n + 1);
    for (int i = 1; i <= n; ++i) ones[i] = ones[i - 1] + (s[i - 1] == '1');

    int total_ones = ones.back(), min_flips = INT_MAX;

    //  0123456 78
    // |1010000|10|  -> 2
    for (int i = 0; i <= n; ++i) {
      int left_ones = ones[i];
      int right_ones = total_ones - left_ones;
      int right_zeros = (n - i) - right_ones;

      min_flips = std::min(min_flips, left_ones + right_zeros);
    }

    return min_flips;
  }
};
