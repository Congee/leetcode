#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  std::vector<int> cache;  // <mask / -1>
  size_t max_len = 0, count = 0;

 public:
  int maxLength(vector<string>& arr) {
    // bitmask every string, just unique characters;
    // backtrack on the bistmask array to find all combinations
    int n = arr.size();
    cache.reserve(n);
    for (int i = 0; i < n; ++i) {
      int mask = 0;
      for (char ch : arr[i]) {
        if (mask & (1 << (ch - 'a'))) {  // in case a string has dup chars
          cache[i] = -1;
          break;
        }

        mask |= 1 << (ch - 'a');
      }
      if (cache[i] != -1) cache[i] = mask;
    }

    dfs(0, 0, arr);
    return max_len;
  }

  void dfs(size_t start, int mask, vector<std::string>& arr) {
    if (start == arr.size()) return;

    for (auto i = start; i < arr.size(); ++i) {
      if (cache[i] == -1) continue;
      if (mask & cache[i]) continue;

      mask |= cache[i];
      count += arr[i].size();

      max_len = std::max(max_len, count);
      dfs(i + 1, mask, arr);

      count -= arr[i].size();
      mask ^= cache[i];
    }
  }
};
