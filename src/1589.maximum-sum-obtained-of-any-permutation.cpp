#ifdef __LOCAL__
#include <leetcode.h>
#endif

const int mod = 1e9 + 7;

class Solution {
 public:
  int maxSumRangeQuery(vector<int>& nums, vector<vector<int>>& requests) {
    return prefix_sum(nums, requests);
    return sweep(nums, requests);
  }

  int prefix_sum(vector<int>& nums, vector<vector<int>>& requests) {
    int n = nums.size();
    std::sort(requests.begin(), requests.end());
    std::vector<int> psum(n + 1, 0);

    for (auto&& req : requests) {
      int lo = req[0], hi = req[1] + 1;
      psum[lo]++;
      psum[hi]--;
    }
    psum.pop_back();

    for (int i = 1; i < n; ++i) psum[i] += psum[i - 1];

    auto rev_cmp = [](const int lhs, const int rhs) { return rhs < lhs; };
    std::sort(nums.begin(), nums.end(), rev_cmp);
    std::sort(psum.begin(), psum.end(), rev_cmp);

    long sum = 0;
    for (int i = 0; i < n && psum[i]; ++i)
      sum = (sum + (long)psum[i] * nums[i] % mod) % mod;
    return sum;
  }

  int sweep(vector<int>& nums, vector<vector<int>>& requests) {
    int n = nums.size();
    // Input: nums = [1,2,3,4,5], requests = [[1,3],[0,1]]
    // Intuition: the more overlapping, the bigger the num to assign

    std::vector<std::pair<int, int>> lines(n);  // <pos, type>
    for (int i = 0; i < n; ++i) lines[i] = {i, 0};

    for (auto&& req : requests) {
      lines.push_back({req[0], +1});
      lines.push_back({req[1] + 1, -1});
    }
    std::sort(lines.begin(), lines.end());

    std::vector<int> vec(n + 1, 0);  // <pos, max_overlap>
    int count = 0;
    for (auto&& [pos, type] : lines) {
      count += type;

      if (type != -1) vec[pos] = std::max(vec[pos], count);
    }
    vec.pop_back();

    auto rev_cmp = [](const int lhs, const int rhs) { return rhs < lhs; };
    std::sort(nums.begin(), nums.end(), rev_cmp);
    std::sort(vec.begin(), vec.end(), rev_cmp);

    // nums = [1,2,3,4,5,10]
    // [0,      2]
    //    [1,1]
    //    [1      3]
    // 10 * 3 + 5 * 2 + 4 * 1 + 3 * 1 = 47
    long sum = 0;
    for (int i = 0; i < n && vec[i]; ++i)
      sum = (sum + (long)vec[i] * nums[i] % mod) % mod;

    return sum;
  }
};
