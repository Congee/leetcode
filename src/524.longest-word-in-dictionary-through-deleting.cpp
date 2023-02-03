#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  string findLongestWord(string& s, vector<string>& dictionary) {
    // TODO: speed up by sorting `dictionary` and finding the first one
    return two_pointers(s, dictionary);
    return by_lcs(s, dictionary);
  }

  string two_pointers(string& s, vector<string>& dictionary) {
    std::string_view result = ""sv;
    for (auto&& word : dictionary) {
      if (word.size() < result.size()) continue;

      int i = 0, j = 0;
      int len = 0;
      while (i < s.size() && j < word.size()) {
        if (s[i] == word[j]) {
          i++, j++, len++;
        } else
          i++;
      }
      if (len < word.size()) continue;

      if (len > result.size())
        result = word;
      else if (len == result.size() && word < result)
        result = word;
    }

    return std::string(result);
  }

  string by_lcs(string& s, vector<string>& dictionary) {
    // LCS sped up with freq counters of chars

    std::array<int, 26> map = {};
    for (char ch : s) map[ch - 'a']++;

    std::string_view result = ""sv;
    for (auto&& word : dictionary) {
      if (word.size() < result.size()) continue;

      std::array<int, 26> freq = {};
      for (char ch : word) freq[ch - 'a']++;
      bool bad = false;
      for (int i = 0; i < 26; ++i)
        if (freq[i] > map[i]) {
          bad = true;
          break;
        }
      if (bad) continue;

      if (lcs(word, s)) {
        if (word.size() > result.size())
          result = word;
        else if (word.size() == result.size() && word < result)
          result = word;
      }
    }

    return std::string(result);
  }

  bool lcs(std::string_view src, std::string_view dst) {
    int m = src.size(), n = dst.size();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));
    for (int i = 1; i < m + 1; ++i) {
      for (int j = 1; j < n + 1; ++j) {
        if (src[i - 1] == dst[j - 1])
          dp[i][j] = dp[i - 1][j - 1] + 1;
        else
          dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
      }
    }

    return dp.back().back() == src.size();
  }
};
