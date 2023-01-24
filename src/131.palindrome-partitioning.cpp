#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  std::vector<std::vector<std::string>> result;
  std::vector<std::string_view> stack;

 public:
  vector<vector<string>> partition(string_view s) { return dp_backtrack(s); }

  vector<vector<string>> dp_backtrack(string_view s) {
    // abbcbba is palindrome
    //  bbcbb  ditto
    std::vector<std::vector<bool>> dp(s.size(), std::vector<bool>(s.size()));
    backtrack(s, 0, dp);
    return result;
  }

  template <typename T>
  void backtrack(string_view s, size_t start, T& dp) {
    if (start == s.size())
      result.push_back(std::vector<std::string>(stack.begin(), stack.end()));

    for (size_t end = start; end < s.size(); ++end) {
      if (s[start] == s[end] && (end - start <= 2 || dp[start + 1][end - 1])) {
        stack.push_back(s.substr(start, end - start + 1));
        dp[start][end] = true;
        backtrack(s, end + 1, dp);
        stack.pop_back();
      }
    }
  }

  void dfs(string_view s, size_t start) {
    if (start == s.size()) {
      result.push_back(std::vector<std::string>(stack.begin(), stack.end()));
      return;
    }

    for (size_t i = start; i < s.size(); ++i) {
      auto sub = s.substr(start, i + 1 - start);
      if (is_palindrome(sub)) {
        stack.push_back(sub);
        dfs(s, i + 1);
        stack.pop_back();
      }
    }
  }

  inline bool is_palindrome(const std::string_view sv) {
    int lo = 0, n = sv.size(), hi = n - 1;

    while (lo < hi)
      if (sv[lo++] != sv[hi--]) return false;

    return true;
  }
};
