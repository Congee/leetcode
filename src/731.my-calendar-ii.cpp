#ifdef __LOCAL__
#include <leetcode.h>
#endif

class MyCalendarTwo {
  // NOTE: Actually a hashmap suffices
  std::multiset<std::pair<int, int>> lines;  // <pos, type>
  static const int k = 2;  // generalized to at most k events in parallel

 public:
  MyCalendarTwo() {}

  bool book(int start, int end) {
    // O(nlogn) + O(n2)
    lines.insert({start, +1});
    lines.insert({end, -1});

    // sweep line
    int max = 0;
    for (auto [pos, type] : lines) {
      max += type;

      if (max == k + 1) {
        lines.erase(lines.find({start, +1}));
        lines.erase(lines.find({end, -1}));
        return false;
      }
    }

    return true;
  }
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo* obj = new MyCalendarTwo();
 * bool param_1 = obj->book(start,end);
 */
