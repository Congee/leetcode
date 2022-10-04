#ifdef __LOCAL__
#include <leetcode.h>
#endif

using Pair = std::pair<int, int>;

void hash_combine(size_t& seed, const int& v) {
  size_t phi = (size_t)(1 << 31) * (std::sqrt(5) - 1) / 2;
  seed ^= phi + std::hash<int>()(v) + (seed << 6) + (seed >> 2);
}

template <>
class std::hash<Pair> {
 public:
  size_t operator()(const Pair& p) const {
    size_t seed = 0;
    hash_combine(seed, p.first);
    hash_combine(seed, p.second);
    return seed;
  }
};

class Solution {
  vector<vector<int>> triangle;
  std::unordered_map<Pair, int> memo;
  int n;

 public:
  int minimumTotal(vector<vector<int>>& __triangle) {
    triangle = std::move(__triangle);
    n = triangle.size();
    // dp(n, i) = curr + min(dp(n + 1, i), dp(n + 1, i + 1));
    return dfs(0, 0);
  }

  long dfs(int row, size_t i) {
    if (row == n) return 0;
    if (i == triangle[row].size()) return INT_MAX;
    auto it = memo.find({row, i});
    if (it != memo.end()) return it->second;

    long r = triangle[row][i] + std::min(dfs(row + 1, i), dfs(row + 1, i + 1));
    return memo[{row, i}] = r;
  }
};
