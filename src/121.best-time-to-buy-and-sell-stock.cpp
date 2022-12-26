#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int maxProfit(vector<int>& prices) { return dp(prices); }

  // kadane
  int dp(vector<int>& prices) {
    int best = 0;
    int min = INT_MAX;
    for (int p : prices) {
      min = std::min(p, min);
      best = std::max(best, p - min);
    }
    return best;
  }

  int weird(vector<int>& prices) {
    if (prices.size() == 1) return 0;

    vector<int> backwards_maximums;
    int max = *prices.rbegin();
    for (auto it = prices.rbegin(); it != prices.rend(); ++it) {
      max = std::max(max, *it);
      backwards_maximums.push_back(max);
    }
    int max_profit = 0;
    int today = prices[0];
    for (int lo = 0, hi = prices.size() - 1; hi > 0; ++lo, --hi) {
      today = std::min(today, prices[lo]);
      max_profit = std::max(max_profit, backwards_maximums[hi] - today);
    }
    return max_profit;
  }
};
