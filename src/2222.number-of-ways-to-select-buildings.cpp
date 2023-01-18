#ifdef __LOCAL__
#include <leetcode.h>
#endif

using Pair = std::pair<long, long>;

class Solution {
 public:
  long long numberOfWays(string s) const { return dp_array(s); }

  long long dp_array(string s) const {
    // optimized from a hashmap version
    long dp[6] = {};
    for (char ch : s) {
      if (ch == '0') {
        dp[0]++;
        dp[1] += dp[3];
        dp[2] += dp[4];
      } else {
        dp[3]++;
        dp[4] += dp[0];
        dp[5] += dp[1];
      }
    }
    return dp[2] + dp[5];
  }

  long long dp_hashmap(string s) {
    std::unordered_map<std::string, long> dp;
    for (char ch : s) {
      if (ch == '0') {
        dp["0"]++;
        dp["10"] += dp["1"];
        dp["010"] += dp["01"];
      } else {
        dp["1"]++;
        dp["01"] += dp["0"];
        dp["101"] += dp["10"];
      }
    }

    return dp["010"] + dp["101"];
  }
};
