#ifdef __LOCAL__
#include <leetcode.h>
#endif

using Pair = std::pair<int, int>;

class Solution {
 public:
  int smallestDistancePair(vector<int>& nums, int k) {
    // offline approach,
    // sort index by value
    // scan to kth pair
    // this approach does not work on case [1,99,100]
    //
    // approach 2
    // enumerate all pairs
    // sort
    // then walk to kth pair
    // Hits memory limit
    //
    // approach 3
    //
    // 1,2,3,4 distance 2 -> 5
    // 1,2,3,3,4 distance 2
    // 1,1,1,3,9,9

    std::sort(nums.begin(), nums.end());

    int lo = 0, hi = nums.back() - nums.front();
    while (lo < hi) {
      int mid = lo + (hi - lo) / 2;

      auto pairs = at_most(nums, mid);
      if (pairs < k)
        lo = mid + 1;
      else
        hi = mid;
    }

    return hi;
  }

  int at_most(vector<int>& nums, int dist) {
    int cnt = 0, lo = 0, hi = 0, n = nums.size();
    for (; hi < n; ++hi) {
      while (nums[hi] - nums[lo] > dist) lo++;
      cnt += hi - lo;
    }
    return cnt;
  }

  int mle(vector<int>& nums, int k) {
    int n = nums.size();
    std::vector<Pair> pairs;

    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        pairs.push_back({nums[i], nums[j]});
      }
    }

    std::sort(pairs.begin(), pairs.end(), [&](const Pair& x, const Pair& y) {
      return std::abs(x.first - x.second) < std::abs(y.first - y.second);
    });

    return std::abs(pairs[k - 1].first - pairs[k - 1].second);
  }
};
