#ifdef __LOCAL__
#include <leetcode.h>
#endif

using vv = vector<vector<int>>;
class Solution {
 public:
  int maximalRectangle(vector<vector<char>>& matrix) {
    // apply the same trick in Largest Rectangle in Histogram
    int m = matrix.size(), n = matrix[0].size(), max_area = 0;

    // in case of hallow
    // 1 1
    // 1 0
    // 1 1
    // ---
    // 3 1
    std::vector<std::vector<int>> heights(m, std::vector<int>(n));
    for (int c = 0; c < n; ++c) {
      for (int r = 0; r < m; ++r) {
        if (matrix[r][c] == '0')
          heights[r][c] = 0;
        else if (r == 0)
          heights[r][c] = 1;
        else
          heights[r][c] = heights[r - 1][c] + 1;
      }
    }

    for (int r = 0; r < m; ++r)
      max_area = std::max(max_area, largest_rect_area(heights[r]));

    return max_area;
  }

  int largest_rect_area(std::vector<int>& heights) {
    int n = heights.size(), max_area = 0;
    heights.push_back(0);
    std::stack<int> stack;  // <idx>

    for (int i = 0; i <= n; ++i) {
      while (stack.size() && heights[stack.top()] > heights[i]) {
        int h = heights[stack.top()];
        stack.pop();
        int w = i - (stack.size() ? stack.top() : -1) - 1;
        max_area = std::max(max_area, w * h);
      }

      stack.push(i);
    }

    heights.pop_back();
    return max_area;
  }
};
