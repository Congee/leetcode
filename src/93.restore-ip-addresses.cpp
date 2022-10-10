#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  std::vector<std::string> vec;
  std::vector<std::string> stack;
  int n;

  inline std::string join() {
    return stack[0] + "." + stack[1] + "." + stack[2] + "." + stack[3];
  }

 public:
  vector<string> restoreIpAddresses(const string& s) {
    n = s.size();

    backtrack(0, s);
    return vec;
  }

  bool backtrack(int idx, const std::string& s) {
    if (stack.size() > 4) return false;
    if (idx == n && stack.size() == 4) vec.push_back(join());
    if (idx == n) return false;

    bool any = false;
    for (int i = idx; i < n && i < idx + 3; ++i) {
      auto seg = s.substr(idx, i - idx + 1);
      if (std::stoi(seg) > 255) continue;
      if (seg.size() > 1 && seg.front() == '0') continue;  // 50.05
      stack.push_back(seg);
      any |= backtrack(i + 1, s);
      stack.pop_back();
    }

    return any;
  }
};
