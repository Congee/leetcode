#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  string subStrHash(const string& s, int power, int modulo, int k, int hashValue) {
    // like rabin-karp backwards
    int n = s.size();
    const auto val = [&](size_t i) { return s[i] - '`'; };
    size_t result = 0;
    long roll = 0;
    long pow_rm = 1;
    for (int i = n - 1; i >= 0; --i) {
      // abcde
      //  cd
      roll = (roll * power + val(i)) % modulo;
      if (i < n - k)
        roll = (roll + modulo - val(i + k) * pow_rm % modulo) % modulo;
      else
        pow_rm = (pow_rm * power) % modulo;

      if (roll == hashValue) result = i;
    }
    return s.substr(result, k);
  }
};
