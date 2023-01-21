#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int longestSubstring(string& s, int k) {
    // cannot do binary search due to lack of monotonicity
    return sliding_window(s, k);
    return dc(s, 0, s.size() - 1, k);
  }

  int sliding_window(string& s, int k) {
    std::array<int, 128> map = {};
    int n = s.size(), max_unique = 0, max_len = 0;
    for (char ch : s) max_unique += ++map[ch] == 1;

    // abababbdabcabc  num_unique = 1
    //      ^^         max_len = 2
    //
    // abababbdabcabc  num_unique = 2
    // ^^^^^^^         max_len = 7
    //
    // abababbdabcabc  num_unique = 3
    //         ^^^^^^  max_len = 6
    for (int num_unique = 1; num_unique <= max_unique; ++num_unique) {
      map = {};
      for (int lo = 0, hi = 0, cnt_unique = 0, upto_k = 0; hi < n; ++hi) {
        cnt_unique += ++map[s[hi]] == 1;
        upto_k += map[s[hi]] == k;

        while (cnt_unique > num_unique) {
          upto_k -= map[s[lo]]-- == k;
          cnt_unique -= map[s[lo++]] == 0;
        }

        if (cnt_unique == num_unique && upto_k == cnt_unique)  // catche up
          max_len = std::max(max_len, hi - lo + 1);
      }
    }

    return max_len;
  }

  int dc(std::string_view s, int start, int end, int k) {
    if (end - start + 1 < k) return 0;

    std::array<int, 26> map = {};
    for (char ch : s.substr(start, end - start + 1)) map[ch - 'a']++;

    bool pass = true;
    for (int i = 0; i < 26 && pass; ++i)
      if (map[i] && map[i] < k) pass = false;

    if (pass) return end - start + 1;

    for (int j = start; j <= end; ++j) {
      if (map[s[j] - 'a'] > 0 && map[s[j] - 'a'] < k) {
        int left = dc(s, start, j - 1, k);
        int right = dc(s, j + 1, end, k);
        return std::max(left, right);
      }
    }

    return end - start + 1;
  }
};
