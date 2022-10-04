#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  vector<int> piles;
  int n;

 public:
  int minEatingSpeed(vector<int>& __piles, int h) {
    piles = std::move(__piles);
    n = piles.size();
    auto [min, max] = std::minmax_element(piles.begin(), piles.end());
    auto lo = 1;
    auto hi = *max;

    while (lo < hi) {
      int mid = lo + (hi - lo) / 2;

      if (eat(mid, h))
        hi = mid;
      else
        lo = mid + 1;
    }

    return hi;
  }

  bool eat(int k, int h) {
    // maybe we can compress piles
    for (int pile : piles) {
      h -= pile / k + (pile % k > 0);
      if (h < 0) return false;
    }
    return true;
  }
};
