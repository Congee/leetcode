#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int longestMountain(vector<int>& arr) {
    // for each peak, expand with two pointers
    // if the tallest two points hav the same height, return 0
    int n = arr.size(), best = 0, max = 0;
    if (n < 3) return 0;

    for (int i = 0; i < n; ++i) {
      //   --
      // /   \
      //
      // \  /
      //  --

      auto at_peak = [&]() {
        bool in_between = i - 1 >= 0 && i + 1 <= n - 1;
        return in_between && arr[i - 1] < arr[i] && arr[i] > arr[i + 1];
      };

      if (at_peak()) {
        int lo = i - 1, hi = i + 1;
        while (lo - 1 >= 0 && arr[lo - 1] < arr[lo]) lo--;
        while (hi + 1 < n && arr[hi] > arr[hi + 1]) hi++;
        best = std::max(best, hi - lo + 1);
      }

      max = std::max(max, arr[i]);
    }

    return best;
  }
};
