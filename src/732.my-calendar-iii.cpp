#ifdef __LOCAL__
#include <leetcode.h>
#endif

class MyCalendarThree {
  std::map<int, int> map;  // <pos, type>
 public:
  MyCalendarThree() {}

  int book(int start, int end) {
    map[start]++;
    map[end]--;  // ensure `end` gets popped first

    int cnt = 0, k = 0;
    for (auto [pos, type] : map) {
      cnt += type;
      k = std::max(k, cnt);
    }

    return k;
  }
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree* obj = new MyCalendarThree();
 * int param_1 = obj->book(startTime,endTime);
 */
