#ifdef __LOCAL__
#include <leetcode.h>
#endif

using Pair = std::pair<int, int>;

template <typename T>
void hash_combine(size_t& seed, const T& v) {
  size_t phi = (size_t)(1 << 31) * (std::sqrt(5) - 1) / 2;
  seed ^= phi + std::hash<T>()(v) + (seed << 6) + (seed >> 2);
}

template <>
class std::hash<Pair> {
 public:
  size_t operator()(const Pair& p) const {
    size_t seed = 0;
    hash_combine(seed, p.first);
    hash_combine(seed, p.second);
    return seed;
  }
};

class Solution {
  vector<vector<int>> points;
  int n;

 public:
  int maxPoints(vector<vector<int>>& __points) {
    points = std::move(__points);
    n = points.size();
    return count_slopes();
  }

  // O(N^2)
  int count_slopes() {
    int max = 1;
    for (int i = 0; i < n; ++i) {
      std::unordered_map<Pair, int> counter;  // <slope, count>
      for (int j = i + 1; j < n; ++j) {
        int dy = points[j][1] - points[i][1];
        int dx = points[j][0] - points[i][0];
        if (dx == 0) {
          counter[{INT_MAX, INT_MAX}]++;
        } else {
          int g = gcd(dx, dy);
          if (g == 0) g = 1;
          Pair slope = {dx / g, dy / g};
          counter[slope]++;
        }
      }
      auto it = std::max_element(
        counter.begin(),
        counter.end(),
        [&](const auto& lhs, const auto& rhs) {
          return lhs.second < rhs.second;
        }
      );
      int local =
        counter.size() ? it->second + 1 : 1;  // don't forget the 1st point
      max = std::max(max, local);
    }
    return max;
  }

  inline int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

  // O(N^3)
  int brutal_force() {
    int max = 1;
    for (int i = 0; i < n; ++i) {
      int xi = points[i][0];
      int yi = points[i][1];
      for (int j = i + 1; j < n; ++j) {
        int xj = points[j][0];
        int yj = points[j][1];
        int count = 2;

        if (xi == xj) {
          for (int k = j + 1; k < n; ++k) {
            int xk = points[k][0];
            if (xk == xi) count++;
          }
        } else {
          // y = ax + b
          double a = ((float)yj - yi) / ((float)xj - xi);
          double b = yi - a * xi;
          for (int k = j + 1; k < n; ++k) {
            int xk = points[k][0];
            int yk = points[k][1];
            if (std::abs(a * xk + b - yk) <= 1e-4F) {
              count++;
            }
          }
        }
        max = std::max(max, count);
      }
    }
    return max;
  }
};
