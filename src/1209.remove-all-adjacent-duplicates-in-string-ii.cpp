#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  std::vector<std::pair<char, int>> stack;  // <char, count>

 public:
  string removeDuplicates(const string& s, int k) {
    int n = s.size();
    if (s.size() < 2) return s;
    // convert to dlist
    // find the first one
    // remove() and expand() -> [(lo, hi), (lo, hi)]  overlap? chunk by hunk
    // repeatedly expand() until impossible

    // aabbbba
    for (int i = 0; i < n; ++i) {
      if (stack.empty()) {
        stack.emplace_back(s[i], 1);
        continue;
      }

      auto [prev_ch, prev_cnt] = stack.back();
      auto count = prev_ch == s[i] ? prev_cnt + 1 : 1;
      stack.emplace_back(s[i], count);

      if (stack.back().second == k)
        for (int j = 0; j < k; ++j) stack.pop_back();
    }

    std::string str;
    str.resize(stack.size());
    for (size_t i = 0; i < stack.size(); ++i) str[i] = stack[i].first;
    return str;
  }
};
