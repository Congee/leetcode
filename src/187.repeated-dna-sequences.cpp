#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  vector<string> findRepeatedDnaSequences(const std::string& s) {
    if (s.size() < 11) return {};

    auto n = s.size();
    int p = 31;
    int m = 1e9 + 7;

    long roll = 0;
    for (size_t i = 0; i < 10; ++i) roll = (roll * p + s[i]) % m;
    long pow_rm = 1;
    for (size_t i = 1; i < 10; ++i) pow_rm = pow_rm * p % m;

    std::unordered_set<std::string> set;
    std::unordered_set<long> seen{
      roll,
    };
    for (size_t i = 10; i < n; ++i) {
      roll = (roll + m - s[i - 10] * pow_rm % m) % m;
      roll = (roll * p + s[i]) % m;

      if (seen.count(roll)) set.insert(s.substr(i - 10 + 1, 10));
      seen.insert(roll);
    }

    return std::vector<std::string>(set.begin(), set.end());
  }
};
