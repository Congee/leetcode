#ifdef __LOCAL__
#include <leetcode.h>
#endif

const int mod = 1e9 + 7;

class Solution {
  std::unordered_map<int, int> cache;  // <idx>
  std::vector<int> arr;
  std::unordered_set<int> set;

 public:
  int numFactoredBinaryTrees(vector<int>& __arr) {
    int n = __arr.size();
    arr = std::move(__arr);
    // sort increasing
    // sum the results of all dfs(element)
    // iter thru num < curr, find curr / num, sum + dfs(num) * dfs(curr / num)
    std::sort(arr.begin(), arr.end());
    set.insert(arr.begin(), arr.end());

    int sum = 0;
    for (int i = 0; i < n; ++i) sum = (sum + dfs(arr[i])) % mod;

    return sum;
  }

  long dfs(int curr) {
    auto it = cache.find(curr);
    if (it != cache.end()) return it->second;

    // [2,4,16]
    // 16
    // 16 - 4 - 4
    // 16 - 4 (2 - 2) - 4
    // 16 - 4 - 4 (2 - 2)
    long sum = 1;
    for (int j = 0; arr[j] < curr; ++j) {
      int num = arr[j];
      if (curr % num == 0 && set.count(curr / num)) {
        sum = (sum + (dfs(num) * dfs(curr / num)) % mod) % mod;
      }
    }
    return cache[curr] = sum;
  }
};
