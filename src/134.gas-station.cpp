#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int n = gas.size();
    // [1, 2, 3, 4, 5]
    // [3, 4, 5, 1, 2]
    // -2,-2,-2, 3, 3
    // -2,-4,-6,-3, 0  sum
    //
    // [2, 3, 4]
    // [3, 4, 3]
    // -1,-1, 1
    // -2,-2,-1  sum
    //
    // prefix sum
    //
    // draw a line of prefix sum by index
    // the next index right next to the lowest point is the answer
    std::vector<int> psum(n);
    int init = 0;
    for (int i = 0; i < n; ++i) {
      psum[i] = gas[i] - cost[i] + init;
      init = psum[i];
    }

    if (psum.back() < 0) return -1;

    auto it = std::min_element(psum.begin(), psum.end());
    return (std::distance(psum.begin(), it) + 1) % n;
  }
};
