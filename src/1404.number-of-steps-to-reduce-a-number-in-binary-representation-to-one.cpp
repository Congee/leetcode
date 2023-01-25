#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int numSteps(string& s) {
    return smart(s);
    return simulate(s);
  }

  int smart(string& s) {
    int count = 0, carry = 0;
    // for each iteration, when carry is 0
    // if the last bit is 0, count += 1;
    // if the last bit is 1, count += 2; carry = 1
    //
    // for each iteration, when carry is 1
    // if the last bit is 0, count += 2; carry is still 1 unchanged
    // if the last bit is 1, count += 1; carry is still 1. remember carry 1 in
    // the last step shall've made this bit 0
    for (size_t i = s.size() - 1; i > 0; --i) {
      count++;
      if (s[i] - '0' + carry == 1) {
        carry = 1;
        count++;
      }
    }

    return count + carry;
  }

  int simulate(string& s) {
    std::vector<bool> vec;
    vec.reserve(s.size());
    for (char ch : s) vec.push_back(ch == '1');

    int count = 0;
    while (!(vec.size() == 1 && vec.back() == 1)) {
      count++;
      if (vec.back() == 0) {
        vec.pop_back();
      } else {
        int i = vec.size() - 1;
        for (; i >= 0; --i)
          if ((vec[i] = vec[i] ^ 1) == 1) break;

        if (i == -1) return count + vec.size();
      }
    }

    return count;
  }
};
