#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  string pushDominoes(string& dominoes) {
    int n = dominoes.size();

    auto handle = [&](int lo, int hi) {
      int dots = hi - lo - 1, mid = lo + (hi - lo) / 2;

      if (0)
        ;
      else if (lo == -1 && hi == n)
        // .....
        return;
      else if (lo == -1) {
        // .....R
        if (dominoes[hi] == 'R') return;
        // ....L
        std::fill(dominoes.begin(), dominoes.begin() + hi, 'L');
      } else if (hi == n) {
        // L....
        if (dominoes[lo] == 'L') return;
        // R....
        std::fill(dominoes.begin() + lo + 1, dominoes.end(), 'R');
      } else if (dominoes[lo] == 'L' && dominoes[hi] == 'R')
        // L.....R
        return;
      else if (dominoes[lo] == 'L' && dominoes[hi] == 'L')
        std::fill(dominoes.begin() + lo, dominoes.begin() + hi, 'L');
      else if (dominoes[lo] == 'R' && dominoes[hi] == 'R')
        std::fill(dominoes.begin() + lo, dominoes.begin() + hi, 'R');
      else if (dominoes[lo] == 'R' && dominoes[hi] == 'L') {
        // R...L
        // R..L
        // R.L
        // RL
        if (dots == 1)
          lo = hi;
        else if (dots & 1) {
          std::fill(dominoes.begin() + lo, dominoes.begin() + mid, 'R');
          std::fill(dominoes.begin() + mid + 1, dominoes.begin() + hi, 'L');
        } else {
          std::fill(dominoes.begin() + lo, dominoes.begin() + mid + 1, 'R');
          std::fill(dominoes.begin() + mid + 1, dominoes.begin() + hi, 'L');
        }
      }
    };

    // find each interval [lo, hi)  X.....X
    //                               l    h
    // fill each interval
    bool lo_set = false;
    for (int lo = 0, hi = 0; hi < n; ++hi) {
      if (dominoes[hi] != '.') continue;

      if (!lo_set) {
        lo_set = true;
        lo = hi;
      }
      while (hi < n && dominoes[hi] == '.') hi++;
      lo_set = false;

      handle(lo - 1, hi);
    }

    return dominoes;
  }
};
