#ifdef __LOCAL__
#include <leetcode.h>
#endif

static constexpr auto powers = [] {
  std::array<int, 1001> pows{};
  for (int i = 1; i <= 1000; ++i) {
    int steps = 0;

    for (int x = i; x != 1;) {
      if (x & 1)
        x = 3 * x + 1;
      else
        x /= 2;

      steps++;
    }

    pows[i] = steps;
  }

  return pows;
}();

class Solution {
  std::unordered_map<std::string, int> memo;

 public:
  int getKth(int lo, int hi, int k) {
    std::vector<std::pair<int, int>> vec;
    for (int i = lo; i <= hi; ++i) vec.push_back({powers[i], i});
    // for (int i = lo; i <= hi; ++i) vec.push_back({steps_of(i, 0), i});

    std::nth_element(vec.begin(), vec.begin() + k - 1, vec.end());
    return vec[k - 1].second;
  }

  int steps_of(int x, int steps) {
    if (x == 1) return steps;
    auto key = std::to_string(x) + '#' + std::to_string(steps);
    auto it = memo.find(key);
    if (it != memo.end()) return it->second;

    if (x & 1)
      return memo[key] = steps_of(3 * x + 1, steps + 1);
    else
      return memo[key] = steps_of(x >> 1, steps + 1);
  }
};
