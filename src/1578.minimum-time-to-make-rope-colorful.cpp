#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int minCost(string& colors, vector<int>& neededTime) {
    return smart(colors, neededTime);
    return stupid(colors, neededTime);
  }

  int smart(string& colors, vector<int>& neededTime) {
    int n = colors.size(), time = 0, psum = 0, max_time = 0;
    for (int i = 0; i < n; ++i) {
      if (i > 0 && colors[i] != colors[i - 1]) {
        time += psum - max_time;
        psum = max_time = 0;
      }

      psum += neededTime[i];
      max_time = std::max(max_time, neededTime[i]);
    }

    time += psum - max_time;
    return time;
  }

  int stupid(string& colors, vector<int>& neededTime) {
    // in a sliding window of m consecutive balloons of the same color, remove m
    // - 1 balloons. that's assuming the cost of removing balloons are the same
    //
    // when costs are different, just keep the one that cost the least
    // use a monotonic stack/queue to keep track of the lowest cost
    int n = colors.size(), time = 0;
    std::vector<int> psum(n + 1);
    std::inclusive_scan(neededTime.begin(), neededTime.end(), psum.begin() + 1);
    std::deque<int> queue;

    for (int lo = 0, hi = 0; hi < n; ++hi) {
      while (queue.size() && neededTime[queue.back()] < neededTime[hi])
        queue.pop_back();
      queue.push_back(hi);

      if ((hi + 1 < n && colors[hi + 1] != colors[hi]) || hi + 1 == n) {
        time += psum[hi + 1] - psum[lo] - neededTime[queue.front()];
        lo = hi + 1;
        queue.clear();
      }
    }

    return time;
  }
};
