#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  double findMaxAverage(vector<int>& nums, int k) {
    // prefix sum is a must
    //
    // cannot do bs as sum or k due to lack of monotonicity;
    // Actually we can, bs on the average!
    //
    // a brutal force solution is loop a window size of k through n, find the
    // maximum of average in each round
    //
    // an important observation is that k shall be as small as possible for a
    // given average

    std::vector<int> psum(nums.size() + 1);
    std::inclusive_scan(nums.begin(), nums.end(), psum.begin() + 1);
    return binary_search(nums, psum, k);
    return brutal_force(psum, nums.size(), k);
  }

  double brutal_force(std::vector<int>& psum, int n, int __k) {
    double max_mean = INT_MIN;                 // do not use FLT_MIN/DBL_MIN
    for (int k = __k; k < 2 * __k - 1; ++k) {  // NOTE: range [k, k * 2)
      for (int lo = 0, hi = k; hi <= n; ++hi, ++lo) {
        auto mean = (psum[hi] - psum[lo]) / (double)k;
        max_mean = std::max(max_mean, mean);
      }
    }
    return max_mean;
  }

  template <typename T>
  double binary_search(T& nums, std::vector<int>& psum, int k) {
    auto [min, max] = std::minmax_element(nums.begin(), nums.end());
    double lo = *min, hi = *max, epsilon = 1e-5;

    double error = INT_MAX, prev_mid = INT_MAX;
    while (error > epsilon) {
      double mid = (lo + hi) * 0.5;

      if (check(psum, nums.size(), mid, k))
        lo = mid;
      else
        hi = mid;

      error = std::abs(mid - prev_mid);
      prev_mid = mid;
    }

    return lo;
  }

  inline bool check(std::vector<int>& psum, int n, double avg, int k) {
    // case
    // [3,6,0,1,8,0]  -> [6,0,1,8]
    // 3
    double min_tail = 0;  // expand tail & head to find the largest range
    for (int i = k; i <= n; ++i) {
      double head = psum[i] - avg * i;
      double tail = psum[i - k] - avg * (i - k);
      min_tail = std::min(min_tail, tail);
      if (head >= min_tail) return true;
    }
    return false;
  }
};
