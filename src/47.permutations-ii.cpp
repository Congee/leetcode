#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  std::vector<std::vector<int>> vec;
  std::vector<int> stack;
  std::vector<int> set;

 public:
  vector<vector<int>> permuteUnique(vector<int>& nums) {
    // two approaches
    // 1. find all permutations and prune results
    // 2. find all permutations and prune on the fly
    set = std::vector<int>(nums.size(), 0);
    std::sort(nums.begin(), nums.end());
    dfs(nums);

    return vec;
  }

  void dfs(std::vector<int>& nums) {
    if (stack.size() == nums.size()) return vec.push_back(stack);

    for (int i = 0; i < nums.size(); ++i) {
      if (set[i]) continue;
      // NOTE: `!set[i - 1]` is the key
      // Let's examine permutations starting with 2
      // [1,1,2]
      //  * * *  -> 2, 1, 1
      //  _ i *  _> backtracking from the above round, [1, 1] became unset. Use
      //            that check do avoid duplicates
      if (i > 0 && nums[i] == nums[i - 1] && !set[i - 1]) continue;

      stack.push_back(nums[i]);
      set[i] = true;
      dfs(nums);
      stack.pop_back();
      set[i] = false;
    }
  }
};
