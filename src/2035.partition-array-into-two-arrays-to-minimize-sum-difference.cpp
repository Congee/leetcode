#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  std::vector<std::pair<int, int>> stack;  // <idx, sum>
  int m, n, total, min_diff;

 public:
  int minimumDifference(vector<int>& nums) {
    m = nums.size();
    n = m / 2;

    return meet_in_the_middle(nums);

    min_diff = INT_MAX;
    total = std::accumulate(nums.begin(), nums.end(), 0);

    return min_diff;
  }

  int meet_in_the_middle(vector<int>& nums) const {
    // Intead of enumerate all possible outcomes with time complecity O(2^N),
    // generate half and half with time complexity O(2^(N/2)) and converge to
    // the target
    //
    // [subarray length][possible sums] e.g., nums = [3,9,7,3] Left [0, n)
    // +-----------------+---------------+
    // | subarray length | possible sums |
    // +=================+===============+
    // | 0               | [0]           |
    // | 1               | [3,9]         |
    // | 2               | [12]          |
    // +-----------------+---------------+
    //
    // Right [n, m)
    // +-----------------+---------------+
    // | subarray length | possible sums |
    // +=================+===============+
    // | 0               | [0]           |
    // | 1               | [7,3]         |
    // | 2               | [10]          |
    // +-----------------+---------------+
    auto lft = generate(nums, 0);
    auto rit = generate(nums, n);
    int total = std::accumulate(nums.begin(), nums.end(), 0);
    int best = INT_MAX, target = total / 2;

    for (int d = 0; d <= n; ++d) {
      auto lhs = lft[d], rhs = rit[n - d];
      std::sort(rhs.begin(), rhs.end());
      for (int sum : lhs) {
        auto it = std::lower_bound(rhs.begin(), rhs.end(), target - sum);
        // want std::abs(total - A) - A) where A = sum + *it
        if (it != rhs.end())
          best = std::min(best, std::abs(total - 2 * (sum + *it)));
      }
    }

    return best;
  }

  std::vector<std::vector<int>> generate(vector<int>& nums, int begin) const {
    std::vector<std::vector<int>> vec(n + 1);  // n + 1 not n because of 0 -> 0
    for (int key = 0; key < (1 << n); ++key) {
      int sum = 0, count = 0;
      // 1001001101
      //       1001
      for (int i = 0; i < n; ++i) {
        if (key & (1 << i)) {
          sum += nums[begin + i];
          count++;
        }
      }

      vec[count].push_back(sum);
    }

    return vec;
  }

  int by_dfs(vector<int>& nums) {
    // backtrack to find all combinations of a binary array [0,1,1,0,1,0]
    // then the time complexity is (1 << 30) ~= 1e8; that's too much
    stack.push_back({0, nums[0]});
    dfs(nums);
    return min_diff;
  }

  void dfs(vector<int>& nums) {
    if (stack.size() == n + 1) return;
    if (stack.size() == n) {
      int sum = stack.back().second;
      min_diff = std::min(min_diff, std::abs((total - sum) - sum));
    }

    for (int i = stack.back().first + 1; i < m; ++i) {
      stack.push_back({i, stack.back().second + nums[i]});
      dfs(nums);
      stack.pop_back();
    }
  }
};
