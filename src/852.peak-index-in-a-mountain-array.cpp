#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int peakIndexInMountainArray(vector<int>& arr) {
    // just binary search

    int n = arr.size(), lo = 0, hi = n - 1;
    while (lo < hi) {
      int mid = lo + (hi - lo) / 2;

      if (arr[mid - 1] < arr[mid] && arr[mid] > arr[mid + 1]) return mid;

      if (arr[mid - 1] <= arr[mid])
        lo = mid;
      else
        hi = mid;
    }

    return -1;
  }
};
