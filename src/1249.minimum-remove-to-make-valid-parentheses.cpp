#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  string minRemoveToMakeValid(string& s) {
    // follow up: 301. Remove Invalid Parentheses
    return mutate(s);
    return record(s);
  }

  string mutate(string& s) {
    std::vector<int> stack;
    for (size_t i = 0; i < s.size(); ++i) {
      if (s[i] == '(')
        stack.push_back(i);
      else if (s[i] == ')') {
        if (stack.size())
          stack.pop_back();
        else
          s[i] = '#';
      }
    }

    for (int idx : stack) s[idx] = '#';

    s.erase(std::remove(s.begin(), s.end(), '#'), s.end());
    return s;
  }

  string record(string& s) const {
    // stack to count invalid parentheses
    std::vector<int> stack;  // pos
    std::unordered_set<int> to_remove;
    for (size_t i = 0; i < s.size(); ++i) {
      char ch = s[i];
      if (std::isalpha(ch)) continue;

      if (ch == '(') {
        to_remove.insert(i);
        stack.push_back(i);
      } else {
        if (stack.size()) {
          to_remove.erase(stack.back());
          stack.pop_back();
        } else {
          to_remove.insert(i);
        }
      }
    }

    std::string valid;
    for (size_t i = 0; i < s.size(); ++i) {
      if (to_remove.count(i)) continue;
      valid += s[i];
    }
    return valid;
  }
};
