#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  vector<int> nums;
  int n;
  std::vector<int> stack;
  std::vector<std::vector<int>> result;

 public:
  vector<vector<int>> subsets(vector<int>& __nums) {
    nums = std::move(__nums);
    n = nums.size();

    result.push_back({});
    for (int i = 1; i < n - 1; ++i) backtrack(0, i);
    result.push_back(nums);

    return result;
  }

  void backtrack(int idx, size_t size) {
    if (stack.size() == size) {
      result.push_back(stack);
      return;
    }

    for (int i = idx; i < n; ++i) {
      stack.push_back(nums[i]);
      backtrack(i + 1, size);
      stack.pop_back();
    }
  }
};
