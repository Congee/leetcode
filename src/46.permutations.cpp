#ifdef __LOCAL__
#include <leetcode.h>
#endif
class Solution {
 public:
  vector<vector<int>> permute(vector<int>& nums) {
    std::vector<vector<int>> result;
    std::vector<int> vec;
    bt(nums, std::set<int>(nums.begin(), nums.end()), vec, result);
    return result;
  }

  void bt(
    vector<int>& nums,
    set<int> set,
    vector<int>& vec,
    std::vector<vector<int>>& result
  ) {
    if (set.empty()) result.push_back(vec);

    for (auto x : set) {
      vec.push_back(x);
      auto copy = set;
      copy.erase(x);
      bt(nums, copy, vec, result);

      vec.pop_back();
    }
  }

  vector<vector<int>> by_stl(vector<int>& nums) {
    std::vector<vector<int>> result;
    int factorial = 1, n = nums.size();
    for (int i = 1; i <= n; ++i) factorial *= i;

    for (int i = 0; i < factorial; ++i) {
      result.push_back(nums);
      std::next_permutation(nums.begin(), nums.end());
    }
    return result;
  }
};
