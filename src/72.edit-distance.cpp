#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  std::vector<std::vector<int>> cache;

 public:
  int minDistance(string word1, string word2) {
    if (word1.empty()) return word2.size();
    if (word2.empty()) return word1.size();

    return edit(word1, word2);

    cache = std::vector<std::vector<int>>(
      word1.size(), std::vector<int>(word2.size(), INT_MIN)
    );
    return lev(word1, word2, 0, 0);
  }

  int edit(string& foo, string& bar) {
    int dp[foo.size() + 1][bar.size() + 1];

    for (int f = 0; f < foo.size() + 1; f++) dp[f][0] = f;
    for (int b = 0; b < bar.size() + 1; ++b) dp[0][b] = b;

    for (int f = 1; f < foo.size() + 1; ++f) {
      for (int b = 1; b < bar.size() + 1; ++b) {
        if (foo[f - 1] == bar[b - 1]) {
          dp[f][b] = dp[f - 1][b - 1];
        } else {
          dp[f][b] = std::min(
            {dp[f - 1][b] + 1, dp[f][b - 1] + 1, dp[f - 1][b - 1] + 1}
          );
        }
      }
    }

    return dp[foo.size()][bar.size()];
  }

  int lev(string& foo, string& bar, int f, int b) {
    if (f == foo.size()) return bar.size() - b;
    if (b == bar.size()) return foo.size() - f;

    if (cache[f][b] != INT_MIN) return cache[f][b];

    auto x = lev(foo, bar, f + 1, b + 1);
    if (foo[f] == bar[b]) return cache[f][b] = x;

    cache[f][b] = 1 +
                  std::min({
                    x,                        // replace
                    lev(foo, bar, f + 1, b),  // insert/delete  flaw <-> lawn
                    lev(foo, bar, f, b + 1)   // insert/delete
                  });

    return cache[f][b];
  }
};
