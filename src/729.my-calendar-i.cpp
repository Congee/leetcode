#ifdef __LOCAL__
#include <leetcode.h>
#endif

class MyCalendar {
  std::set<std::pair<int, int>> tree;  // a vector is faster

 public:
  MyCalendar() {}

  bool book(int start, int end) {
    if (tree.empty()) {
      tree.insert({start, end});
      return true;
    }

    auto it = tree.lower_bound({start, end});
    if (it == tree.end() && tree.size() && std::prev(it)->second > start) return false;
    if (it != tree.end() && end > it->first) return false;
    if (it != tree.end() && std::distance(tree.begin(), it) >= 1 && std::prev(it)->second > start) return false;

    tree.insert({start, end});
    return true;
  }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */
