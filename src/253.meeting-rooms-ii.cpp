#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int minMeetingRooms(vector<vector<int>>& intervals) {
    int n = intervals.size();
    if (n < 2) return n;

    std::sort(
      intervals.begin(),
      intervals.end(),
      [](std::vector<int>& a, std::vector<int>& b) { return a[0] < b[0]; }
    );

    // min heap
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;

    pq.push(intervals[0][1]);
    for (int i = 1; i < n; ++i) {
      if (intervals[i][0] >= pq.top()) {
        pq.pop();
      }

      pq.push(intervals[i][1]);
    }

    return pq.size();
  }
};

// [[0,30],[5,10],[15,20]]
// [[0,30],[30,40]]
// [[7,10],[2,4]]
// [[5,8],[6,8]]
// [[2,11],[6,16],[11,16]]
