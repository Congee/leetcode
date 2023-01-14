#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int bagOfTokensScore(vector<int>& tokens, int power) {
    // [100,200,300,400], power = 200
    // sort ASC
    // prefix sum
    // greedy
    //    when needing score, go from left
    //    when needing power, go from right
    // at each step from left, max(sum scores from left, prev), go next round

    int n = tokens.size(), score = 0, max_score = 0;
    std::sort(tokens.begin(), tokens.end());

    for (int lo = 0, hi = n - 1; lo <= hi;) {
      if (power < tokens[lo] && score == 0) break;

      while (lo <= hi && power >= tokens[lo]) {
        power -= tokens[lo++];
        max_score = std::max(max_score, ++score);
      }

      while (lo <= hi && power < tokens[lo] && score > 0) {
        power += tokens[hi--];
        score--;
      }
    }

    return max_score;
  }
};
