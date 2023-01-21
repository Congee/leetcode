#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
    // prefix sum by range
    // diff array
    std::vector<int> psum(n + 1);
    for (auto&& v : bookings) {
      int first = v[0], last = v[1], seats = v[2];
      psum[first - 1] += seats;
      psum[last] -= seats;
    }

    for (int i = 1; i < n; ++i) psum[i] = psum[i - 1] + psum[i];
    psum.pop_back();
    return psum;
  }
};
