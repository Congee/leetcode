#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int maxArea(vector<int>& height) {
    // |      |
    // |      |
    // | |    |  |
    // | |    |  |

    //     |     |
    //     |     |
    //     |     |
    //     |     |
    // |   |     |   |
    // |   |     |   |
    int area = 0;
    // always move the shorter line
    for (int lo = 0, hi = height.size() - 1; lo < hi;) {
      area = std::max(area, (hi - lo) * std::min(height[lo], height[hi]));
      height[lo] < height[hi] ? ++lo : --hi;
    }

    return area;
  }
};
