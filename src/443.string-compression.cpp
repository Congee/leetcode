#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int compress(vector<char>& chars) {
    int n = chars.size();
    int lo = 0;
    int hi = 0;
    chars.push_back('\0');

    int ptr = 0;
    char curr = chars[0];
    for (; hi < n + 1; ++hi) {
      if (chars[hi] == curr) continue;

      int cnt = hi - lo;
      if (cnt == 1) {
        chars[ptr++] = curr;
      } else {
        chars[ptr++] = curr;
        for (char c : std::to_string(cnt)) {
          chars[ptr++] = c;
        }
      }
      curr = chars[hi];
      lo = hi;
    }

    chars.pop_back();
    return ptr;
  }
};
