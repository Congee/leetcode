#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  vector<int> goodIndices(vector<int>& nums, int k) {
    int n = nums.size();

    std::unordered_set<int> good;
    std::vector<int> vec;

    // non-decreasing
    for (int i = n - 2, count = 1; i >= k; --i) {
      if (count >= k) good.insert(i);

      if (nums[i] <= nums[i + 1])
        count++;
      else
        count = 1;
    }


    // non-increasing
    for (int i = 1, count = 1; i < n - k; ++i) {
      if (count >= k && good.count(i)) vec.push_back(i);

      if (nums[i] <= nums[i - 1])
        count++;
      else
        count = 1;
    }

    return vec;
  }
};
