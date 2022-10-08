#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  vector<int> price;
  vector<int> tastiness;
  int n;
  std::vector<std::vector<std::vector<int>>> memo;  // [coupon, size, amount]

 public:
  int maxTastiness(
    vector<int>& __price,
    vector<int>& __tastiness,
    int maxAmount,
    int maxCoupons
  ) {
    price = std::move(__price);
    tastiness = std::move(__tastiness);
    n = price.size();
    memo.assign(
      maxCoupons + 1,
      std::vector<std::vector<int>>(n, std::vector<int>(maxAmount + 1, -1))
    );

    // dp(i, amount, coupons) = max [ dp(i + k, amount - price[n], coupons - ?) | k <- i..n-k ]
    return dfs(0, maxAmount, maxCoupons);
  }

  int dfs(int idx, int amount, int coupons) {
    if (amount < 0) return INT_MIN;
    if (coupons < 0) return INT_MIN;
    if (amount == 0) return 0;
    if (idx == n) return 0;

    auto& cache = memo[coupons][idx][amount];
    if (cache != -1) return cache;

    int max = 0;
    for (int i = idx; i < n; ++i) {
      max = std::max({
        max,
        tastiness[i] + dfs(i + 1, amount - price[i], coupons),
        tastiness[i] + dfs(i + 1, amount - price[i] / 2, coupons - 1),
      });
    }

    return cache = max;
  }
};
