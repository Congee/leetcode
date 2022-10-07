#ifdef __LOCAL__
#include <leetcode.h>
#endif

// Another Two Sum
class Solution {
  int nCr(int n, int r) {
    // n! / r!(n - r)!
    return round(tgamma(n + 1) / tgamma(r + 1) / tgamma(n - r + 1));
  }

 public:
  int tupleSameProduct(vector<int>& nums) {
    int n = nums.size();

    std::unordered_map<int, int> map;  // <idx, _>
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        map[nums[i] * nums[j]]++;
      }
    }

    int count = 0;
    for (auto&& [_, s] : map) {
      if (s == 1) continue;
      // (1,2), (3,4), (5,6)
      count += 8 * nCr(s, 2);
    }
    return count;
  }
};

static const size_t phi = (size_t)(1 << 31) * (std::sqrt(5) - 1) / 2;

void hash_combine(size_t& seed, const int& v) {
  seed ^= phi + std::hash<int>()(v) + (seed << 6) + (seed >> 2);
}

template <>
class std::hash<std::vector<int>> {
 public:
  size_t operator()(const std::vector<int>& vec) const {
    size_t seed = 0;
    hash_combine(seed, vec[0]);
    hash_combine(seed, vec[1]);
    hash_combine(seed, vec[2]);
    hash_combine(seed, vec[3]);
    return seed;
  }
};

class TLE : Solution {
 public:
  int tupleSameProduct(vector<int>& nums) {
    int n = nums.size();
    std::unordered_map<int, int> map;  // <num, idx>
    for (int i = 0; i < n; ++i) map[nums[i]] = i;

    std::unordered_set<std::vector<int>> set;

    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        auto prod = nums[i] * nums[j];
        for (int k = 0; k < n; ++k) {
          if (k == i || k == j) continue;

          int quotient = prod / nums[k];
          auto it = map.find(quotient);
          if (it != map.end()) {
            int quot_idx = it->second;
            if (quot_idx != i && quot_idx != j && quot_idx != k) {
              std::vector<int> tmp{i, j, k, quot_idx};
              std::sort(tmp.begin(), tmp.end());
              set.insert(tmp);
            }
          }
        }
      }
    }
    // 2 6, 3, 4
    // 2 6, 4, 3
    return set.size() * 8;
  }
};
