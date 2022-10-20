#ifdef __LOCAL__
#include <leetcode.h>
#endif

using Pair = std::pair<int, int>;

class Solution {
 public:
  int fourSumCount(
    vector<int>& nums1,
    vector<int>& nums2,
    vector<int>& nums3,
    vector<int>& nums4
  ) {
    return v2(nums1, nums2, nums3, nums4);
  }

  int v2(
    vector<int>& nums1,
    vector<int>& nums2,
    vector<int>& nums3,
    vector<int>& nums4
  ) {
    std::unordered_map<int, int> map;  // <sum34, [idx]>

    for (int i : nums3) {
      for (int j : nums4) {
        map[i + j]++;
      }
    }

    int count = 0;
    for (int i : nums1) {
      for (int j : nums2) {
        count += map[-i - j];
      }
    }
    return count;
  }

  int v1(
    vector<int>& nums1,
    vector<int>& nums2,
    vector<int>& nums3,
    vector<int>& nums4
  ) {
    int n = nums1.size();
    std::unordered_map<int, std::vector<Pair>> map;  // <sum34, [idx]>

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        map[nums3[i] + nums4[j]].push_back({i, j});
      }
    }

    int count = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        count += map[-nums1[i] - nums2[j]].size();
      }
    }

    return count;
  }
};
