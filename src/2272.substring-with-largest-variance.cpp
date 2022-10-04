#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  int n;
  std::array<std::vector<int>, 26> sum;

 public:
  int largestVariance(std::string_view s) {
    n = s.size();

    std::unordered_set<char> unique(s.begin(), s.end());
    std::string str(unique.begin(), unique.end());

    int result = 0;
    for (char a : str) {
      for (char b : str) {
        // kadane
        int variance = 0;
        bool has_b = false;
        bool startswith_b = false;
        for (char ch : s) {
          variance += ch == a;
          if (ch == b) {
            has_b = true;
            if (startswith_b && variance >= 0)
              startswith_b = false;
            else if (--variance < 0) {
              startswith_b = true;
              variance = -1;
            }
          }
          result = std::max(result, has_b ? variance : 0);
        }
      }
    }

    return result;
  }

  // TLE
  int naive_dp(std::string_view& s) {
    // dp(i, j) = max(diff, dp(i, k), ...., dp(k, j))
    for (auto&& v : sum) {
      v.resize(n + 1);
      v[0] = 0;
    }

    // 1 0 0 1
    // 1 1 1 2
    // 0 1 1 1 2
    for (int i = 0; i < 26; ++i) {
      for (int j = 0; j < n; ++j) {
        sum[i][j + 1] = sum[i][j] + (s[i] - 'a' == i);
      }
    }

    return dfs(s, 0, n - 1);
  }

  int diff(int i, int j) {
    int max = 0;
    for (int x = 0; x < 26; ++x) max = std::max(max, sum[x][j] - sum[x][i]);
    return max;
  }

  int dfs(std::string_view& s, int i, int j) {
    if (i > j) return 0;
    if (i == j) return 1;

    auto curr = diff(i, j + 1);
    int max = curr;
    for (int k = i + 1; k <= j; ++k) {
      max = std::max({max, dfs(s, i, k), dfs(s, k + 1, j)});
    }
    return max;
  }
};
