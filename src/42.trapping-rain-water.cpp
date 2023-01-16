#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int trap(vector<int>& height) {
    return simple_two_pass(height);
    return monotomic_stack(height);
    return two_pointers(height);
    return dynamic_programming(height);
    return brutal(height);
  }

  int simple_two_pass(vector<int>& height) {
    // find the global maxium pos_max
    // scan from left to pos_max; calc a colum with the rolling max and curr
    // scan from right to pos_max; do the same
    auto pos_max = std::max_element(height.begin(), height.end());

    auto trapped = [&](auto begin, auto end) -> int {
      int max = 0;
      return std::accumulate(begin, end, 0, [&](int acc, int curr) {
        if (curr > max)
          max = curr;
        else
          acc += max - curr;
        return acc;
      });
    };

    return trapped(height.begin(), pos_max) +
           trapped(height.rbegin(), make_reverse_iterator(pos_max));
  }

  int two_pointers(vector<int>& height) {
    int n = height.size(), amount = 0, lo = 0, hi = n - 1, level = 0;

    while (lo < hi) {
      // move pointer to holder as much water as possible
      int lower = height[height[lo] < height[hi] ? lo++ : hi--];  // bottom
      level = std::max(level, lower);  // surface from the prev/curr taller bar
      amount += level - lower;
    }

    return amount;
  }

  int dynamic_programming(vector<int>& height) {
    // adapted from the brutal force approach
    // just cache max values on both directions
    // NOTE: the state can be compressed from O(2n) to O(n)
    // NOTE: this approach probably has better locality than the two pointers
    int n = height.size(), amount = 0;

    std::vector<int> left_max(n), right_max(n);
    left_max[0] = height[0];
    right_max.back() = height.back();
    for (int i = 1, r = n - 2; i < n; ++i, --r) {
      left_max[i] = std::max(left_max[i - 1], height[i]);
      right_max[r] = std::max(right_max[r + 1], height[r]);
    }

    for (int i = 1, r = n - 1; i < n - 1; ++i, --r)
      amount += std::min(left_max[i], right_max[i]) - height[i];

    return amount;
  }

  int monotomic_stack(vector<int>& height) {
    // maintain a monotonically decreasing stack; we add row by row
    // use stack.pop(), then stack.top(), and curr
    //
    // suppose we are at 1
    // popped = stack.pop();
    // w = curr - stack.top() - 1;   // 2 - 0 - 1
    // h = min(stack.top(), curr) - popped
    // answer += w * h
    // |
    // | * * |
    // | x | |
    // | | | |
    // 0 1 2 3

    int n = height.size(), amount = 0;
    std::stack<int> stack;
    for (int i = 0; i < n; ++i) {
      while (stack.size() && height[stack.top()] < height[i]) {  // decreasing
        int j = stack.top();
        stack.pop();

        if (stack.size()) {
          int h = std::min(height[stack.top()], height[i]) - height[j];
          int w = i - stack.top() - 1;
          amount += h * w;
        }
      }

      stack.push(i);
    }

    return amount;
  }

  int brutal(vector<int>& height) {
    int n = height.size(), amount = 0;

    // find the maxium capacity of each column, and sum these capacities
    //               |
    //       | x x x |
    //   | x | | x | |
    // 0 1 2 3 4 5 6 7
    // 0 1 0 2 1 0 1 3
    //   0+1+0+1+2+1  = 5

    for (int i = 1; i < n - 1; ++i) {
      int left_max = 0, right_max = 0;

      for (int j = i; j >= 0; --j) left_max = std::max(left_max, height[j]);

      for (int j = i; j < n; ++j) right_max = std::max(right_max, height[j]);

      amount += std::min(left_max, right_max) - height[i];
    }
    return amount;
  }
};
