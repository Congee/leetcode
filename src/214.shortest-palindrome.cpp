#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  // ab -> a ab
  // "" -> "a"
  // abc -> cb abc
  // acc -> cc acc
  // aacecaaa ->         _765  43210 4
  // aacecaaa ->         0124  4567_ 4
  // aacecaaa -> _       aace  caaa_ 4
  // aacecaaa -> a       aac e caaa_ 4 + 1 Y
  // aacecaaa -> aa      aac  ecaaa_ 5
  // aacecaaa -> aaa     aa c ecaaa_ 5 + 1
  // aacecaaa -> aaac    aa  cecaaa_ 6
  // aacecaaa -> aaaca   a a cecaaa_ 6 + 1
  // aacecaaa -> aaacac  a  acecaaa_ 7
  // aacecaaa -> aaaceca a  acecaaa_ 7 + 1 Y
  string shortestPalindrome(const string& s) {
    int n = s.size();
    if (n <= 1) return s;

    int p = 31;
    int m = 1e9 + 7;

    std::vector<long> pows(n);
    pows[0] = 1;
    for (int i = 1; i < n; ++i)
      pows[i] = (pows[i - 1] * p) % m;

    std::vector<long> rights(n);  // TODO
    rights.push_back(0);
    for (int i = 1; i < n; ++i) {
      // 3210
      // abc
      rights[i] = (rights[i - 1] * p + s[n - i - 1]) % m;
    }

    long mid = 0;
    // [0, 4), half of len 8
    for (int i = 0; i < n / 2; ++i)
      mid = (mid * p) % m;

    // left can be derived from right
    for (int i = n - 1, size = n / 2; i >= 1; --i) {
      int oppo = n - i - 1;
      // even
      // 0 <-> 7 of len 8
      long left = rights[oppo];
      // 0 <-> 7 of len 8, @ 4
      long right = rights[(n / 2)];
      if (left + mid == right) return s.substr(i, n - i) + s;

      mid = (mid + m - s[(oppo + size - 1)] * pows[oppo + size - 1] % m) % m;
      mid = (mid * p) % m;

      // odd
    }

    return "";
  }
};
