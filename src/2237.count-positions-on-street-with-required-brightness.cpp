#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int meetRequirement(
    int n, vector<vector<int>>& lights, vector<int>& requirement
  ) {
    return prefix_sum(n, lights, requirement);
    return sweep(n, lights, requirement);
  }

  int prefix_sum(int n, vector<vector<int>>& lights, vector<int>& requirement) {
    std::vector<int> vec(n + 1, 0);
    for (auto&& light : lights) {
      int lo = std::max(0, light[0] - light[1]);
      int hi = std::min(n, light[0] + light[1] + 1);
      vec[lo]++;
      vec[hi]--;
    }

    for (int i = 1; i <= n; ++i) vec[i] += vec[i - 1];

    int good = 0;
    for (int i = 0; i < n; ++i) good += vec[i] >= requirement[i];
    return good;
  }

  int sweep(int n, vector<vector<int>>& lights, vector<int>& requirement) {
    std::vector<int> vec(n + 1, 0);

    for (auto&& light : lights) {
      int lo = std::max(0, light[0] - light[1]);
      int hi = std::min(n, light[0] + light[1] + 1);  // closed to open range
      vec[lo]++;
      vec[hi]--;
    }

    int curr = 0, good = 0;
    for (int i = 0; i < n; ++i) {
      curr += vec[i];
      good += curr >= requirement[i];
    }
    return good;
  }

  int clunky(int n, vector<vector<int>>& lights, vector<int>& requirement) {
    std::unordered_map<int, int> neg;              // <pos, cnt>
    std::vector<std::tuple<int, int, int>> lines;  // <pos, type, req>
    for (auto&& light : lights) {
      int lo = std::max(0, light[0] - light[1]);
      int hi = std::min(n - 1, light[0] + light[1]);
      lines.push_back({lo, +1, INT_MIN});
      lines.push_back({hi, -1, INT_MIN});
    }

    for (int i = 0; i < n; ++i) lines.push_back({i, 2, requirement[i]});

    std::sort(lines.begin(), lines.end());

    int cnt = 0, good = 0;
    for (auto&& [pos, type, req] : lines) {
      if (type != 2) cnt += type;

      if (type == -1) neg[pos]++;

      if (type == 2) good += cnt + neg[pos] >= requirement[pos];
    }
    return good;
  }
};
