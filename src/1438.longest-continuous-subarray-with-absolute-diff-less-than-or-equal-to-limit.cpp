#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int longestSubarray(vector<int>& nums, int k) {
    return monotonic_queue(nums, k);
  }

  int monotonic_queue(vector<int>& nums, int k) {
    std::deque<int> maxq, minq;
    int lo = 0;
    for (size_t hi = 0; hi < nums.size(); ++hi) {
      while (maxq.size() && maxq.back() < nums[hi]) maxq.pop_back();
      while (minq.size() && minq.back() > nums[hi]) minq.pop_back();
      maxq.push_back(nums[hi]);
      minq.push_back(nums[hi]);

      // lo and hi will be updated at most once per iteration
      // shrinking once does not make our answer smaller cuz hi will be updated
      // so we can update lazily lo instead of using a while loop
      if (maxq.front() - minq.front() > k) {
        if (maxq.front() == nums[lo]) maxq.pop_front();
        if (minq.front() == nums[lo]) minq.pop_front();
        lo++;
      }
    }

    return nums.size() - lo;
  }

  int naive(vector<int>& nums, int k) {
    // sliding window of a treeset that maintains min & max

    size_t n = nums.size(), len = 1;
    std::multiset<int> tree;
    for (size_t lo = 0, hi = 0; hi < n; ++hi) {
      tree.insert(nums[hi]);

      while (tree.size() && std::abs(*tree.begin() - *tree.rbegin()) > k)
        tree.erase(tree.find(nums[lo++]));

      len = std::max(len, tree.size());
    }

    return len;
  }
};
