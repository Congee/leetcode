#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  long min = INT_MAX;

 public:
  int closestCost(vector<int>& bases, vector<int>& ts, int target) {
    return easy_dp(bases, ts, target);
  }

  int easy_dp(vector<int>& bases, vector<int>& ts, int target) {
    const int min = *std::min_element(bases.begin(), bases.end());
    if (min >= target) return min;
    // for all number > 2 * target - min; number - target > min - target
    const int kmax = 2 * target - min;

    std::vector<bool> dp(kmax + 1);
    for (int base : bases)
      if (base <= kmax) dp[base] = 1;

    for (int topping : ts) {
      // backwards because,
      // dp[x], dp[x + t], dp[x + t * 2]
      // when x reaches (x + t), dp[(x + t) + t] will be set also
      // we only want 3 cases
      for (int x = kmax; x >= min; --x) {
        // only when dp[x] == true, [x + topping] & [x + topping * 2] make sense
        if (dp[x] == 0) continue;

        if (x + topping * 1 <= kmax) dp[x + topping * 1] = 1;
        if (x + topping * 2 <= kmax) dp[x + topping * 2] = 1;
      }
    }

    int min_diff = INT_MAX, ans = min;
    for (int x = min; x < kmax + 1; ++x) {
      if (dp[x] == 0) continue;

      const int diff = std::abs(x - target);
      if (diff < min_diff || (diff == min_diff && x < ans)) {
        min_diff = diff;
        ans = x;
      }
    }

    return ans;
  }

  int elusive_dp(vector<int>& bases, vector<int>& ts, int target) {
    // 1 <= n, m <= 10

    // knapsack dp
    // [min, upper - 1]
    int min_diff = INT_MAX, ans = INT_MAX;
    int min = *std::min_element(bases.begin(), bases.end());
    const int kmax = 2 * std::accumulate(ts.begin(), ts.end(), 0) - min;
    std::vector<bool> dp(kmax + 1);
    dp[0] = 1;

    // [b1,b2,b3]
    // [b1,b2,b3,b1+x,b2+x,b3+x,b1+2x,b2+2x,b3+2x]
    for (int topping : ts) {
      for (int k = kmax; k >= 0; --k) {
        if (dp[k] == 0) continue;
        // if (k + 0 * topping <= kmax) dp[k + 0 * topping] = 1;
        if (k + 1 * topping <= kmax) dp[k + 1 * topping] = 1;
        if (k + 2 * topping <= kmax) dp[k + 2 * topping] = 1;
      }
    }

    for (int k = 0; k <= kmax; ++k) {
      if (dp[k] == 0) continue;

      for (int base : bases) {
        const int diff = std::abs(base + k - target);
        if (diff < min_diff || (diff == min_diff && base + k < ans)) {
          min_diff = diff;
          ans = base + k;
        }
      }
    }

    return ans;

    // brutal force
    for (int base : bases) {
      dfs(0, base, 0, ts, target);
      dfs(0, base, 1, ts, target);
      dfs(0, base, 2, ts, target);
    }

    return min;
  }

  void dfs(
    int start, long total, int8_t one, vector<int>& toppings, int target
  ) {
    if (start == toppings.size()) return;

    long sum = total + toppings[start] * one;
    if (one && std::abs(sum - target) < std::abs(min - target))
      min = sum;
    else if (one && std::abs(sum - target) < std::abs(min - target))
      min = std::min(min, sum);

    dfs(start + 1, sum, 0, toppings, target);
    dfs(start + 1, sum, 1, toppings, target);
    dfs(start + 1, sum, 2, toppings, target);
  }
};
