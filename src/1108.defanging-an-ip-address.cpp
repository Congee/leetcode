#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  string defangIPaddr(const string& address) {
    std::string str;

    for (char ch : address) {
      if (ch == '.') {
        str += "[.]";
      } else {
        str += ch;
      }
    }

    return str;
  }
};
