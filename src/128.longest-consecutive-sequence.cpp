#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  std::vector<int> nums;
  std::unordered_set<int> set;
  std::unordered_set<int> seen;
  int n;

 public:
  int longestConsecutive(vector<int>& __nums) {
    nums = std::move(__nums);
    n = nums.size();

    set.insert(nums.begin(), nums.end());
    int max = 1;
    for (int num : set) {
      if (seen.count(num) == 0) max = std::max(max, dfs(num));
    }
    return max;
  }

  int dfs(int num) {
    if (seen.count(num)) return 0;
    if (!set.count(num)) return 0;

    return 1 + dfs(num - 1) + dfs(num + 1);
  }
};
