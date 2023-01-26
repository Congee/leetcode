#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int largestRectangleArea(vector<int>& heights) {
    // starting from a brutal force approach
    // |_____x__|
    // |+_+++x__]
    // for each x, scan to left. keep track of min height while caclculating
    // the largest valid area

    int n = heights.size(), max_area = 0;
    std::vector<int> stack;  // <idx>
    heights.push_back(0);    // for the rightmost element

    for (int i = 0; i <= n; ++i) {
      while (stack.size() && heights[stack.back()] > heights[i]) {
        int h = heights[stack.back()];
        stack.pop_back();
        int w = i - (stack.size() ? stack.back() : -1) - 1;
        max_area = std::max(max_area, h * w);
      }

      stack.push_back(i);
    }

    heights.pop_back();
    return max_area;
  }
};
