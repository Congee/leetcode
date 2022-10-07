#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  vector<bool> camelMatch(vector<string>& queries, const std::string& pattern) {
    std::vector<bool> vec(queries.size());
    for (size_t i = 0; i < queries.size(); ++i)
      vec[i] = match(queries[i], pattern);
    return vec;
  }

  bool match(const std::string& str, const std::string& pattern) {
    if (str.size() < pattern.size()) return false;

    // FooBarTest, FrameBuffer
    // FoBaTa

    size_t up = 0;
    size_t dn = 0;
    while (up < str.size() && dn < pattern.size()) {
      // FooBar
      // FoT
      while (up < str.size() && str[up] != pattern[dn]) {
        if (std::isupper(str[up]))
          return false;
        else
          up++;
      }

      //
      if (up == str.size()) return false;

      if (str[up] == pattern[dn]) {
        up++;
        dn++;
      }
    }

    if (dn < pattern.size()) return false;

    for (; up < str.size(); ++up)
      if (std::isupper(str[up])) return false;
    return true;
  }
};
