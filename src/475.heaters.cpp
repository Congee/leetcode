#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int findRadius(vector<int>& houses, vector<int>& heaters) {
    // [1, 2, 3]
    //  -  2  -       -> min radius = 1
    //
    // [1, , , , , 5]
    //  1   - - 4    -> min radius = 2
    //
    // [1,2,3]
    //      3,4,5,6
    return two_ptrs(houses, heaters);
    return bs(houses, heaters);
  }

  int bs(vector<int>& houses, vector<int>& heaters) const {
    const std::set<int> tree(heaters.begin(), heaters.end());
    int max_radius = 0;
    for (auto&& house : houses) {
      auto lit = tree.lower_bound(house);
      auto rit = tree.lower_bound(house);
      lit = lit == tree.begin() ? lit : std::prev(lit);
      rit = rit == tree.end() ? std::prev(rit) : rit;

      auto min = std::min(std::abs(*lit - house), std::abs(*rit - house));
      max_radius = std::max(max_radius, min);
    }
    return max_radius;
  }

  int two_ptrs(vector<int>& houses, vector<int>& heaters) {  // both right bound
    // like in merge sort
    std::sort(houses.begin(), houses.end());
    std::sort(heaters.begin(), heaters.end());

    // traverse houses, and mess with the radius of the two closest heaters
    int max_radius = 0, m = heaters.size(), heater_idx = 0;
    for (auto&& house : houses) {
      for (; heater_idx < m && heaters[heater_idx] < house; heater_idx++)
        ;

      int radius = std::min(
        heater_idx > 0 ? house - heaters[heater_idx - 1] : INT_MAX,  // left
        heater_idx < m ? heaters[heater_idx - 0] - house : INT_MAX   // right
      );

      max_radius = std::max(max_radius, radius);
    }
    return max_radius;
  }
};
