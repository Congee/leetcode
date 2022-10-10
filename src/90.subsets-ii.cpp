#ifdef __LOCAL__
#include <leetcode.h>
#endif

void hash_combine(size_t& seed, const int& v) {
  static const size_t phi = (size_t)(1 << 31) * (std::sqrt(5) - 1) / 2;
  seed ^= phi + std::hash<int>()(v) + (seed << 6) + (seed >> 2);
}

namespace std {
template <>
class hash<std::vector<int>> {
 public:
  size_t operator()(const std::vector<int>& vec) const {
    size_t seed = 0;
    for (auto&& num : vec) hash_combine(seed, num);
    return seed;
  }
};
}  // namespace std

class Solution {
 public:
  vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    // [1,2,1] ??? {1,2} == {2,1}
    std::sort(nums.begin(), nums.end());
    // dp
    std::vector<std::vector<int>> vec;
    vec.push_back({});

    int m = 0;
    for (size_t i = 0; i < nums.size(); ++i) {
      int start = i >= 1 && nums[i - 1] == nums[i] ? m : 0;
      // 1 *1* 2
      // {{}, {1}, { starts here with {1} than {}, }}
      
      m = vec.size();
      for (int j = start; j < m; ++j) {
        vec.push_back(vec[j]);
        vec.back().push_back(nums[i]);
      }
    }

    return vec;
    // slow
    std::unordered_set<std::vector<int>> set(vec.begin(), vec.end());
    return vector<std::vector<int>>(set.begin(), set.end());
  }
};
