#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  // [3,-1,10] 10
  // -> 1
  // [3,-1,10] 12
  // -> 3
  // [4,-1,3,-1,10] 10
  // -> 1
  int shortestSubarray(vector<int>& nums, int k) {
    int n = nums.size(), shortest = INT_MAX;
    std::vector<long> psum(n + 1);
    psum[0] = 0;
    for (int i = 0; i < n; ++i) psum[i + 1] = psum[i] + nums[i];

    std::deque<int> queue;
    for (int i = 0; i < n + 1; ++i) {
      // XXX: negative tails are useless. This is the key
      while (queue.size() && psum[i] - psum[queue.back()] <= 0)
        queue.pop_back();

      while (queue.size() && psum[i] - psum[queue.front()] >= k) {
        shortest = std::min(shortest, i - queue.front());
        queue.pop_front();
      }

      queue.push_back(i);
    }

    return shortest < INT_MAX ? shortest : -1;
  }
};
