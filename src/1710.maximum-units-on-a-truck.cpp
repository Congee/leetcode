#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
    // sort by units
    // add from big to small

    std::sort(
      boxTypes.begin(), boxTypes.end(),
      [&](const auto& lhs, const auto& rhs) { return lhs[1] > rhs[1]; }
    );

    int sum = 0;
    int size = 0;
    for (auto&& box : boxTypes) {
      int count = box[0];
      int units = box[1];
      auto mul = std::min(truckSize - size, count);
      sum += mul * units;
      size += mul;
      if (size == truckSize) break;
    }

    return sum;
  }
};
