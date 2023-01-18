#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int numWaterBottles(int numBottles, int numExchange) {
    // total, empty_remain
    // exit when empty_remain < exchange
    int total = 0, empty = 0, bottles = numBottles;
    while (true) {
      total += bottles;
      empty += bottles;

      bottles = empty / numExchange;
      empty %= numExchange;

      if (bottles + empty < numExchange) {
        total += bottles;
        break;
      }
    }

    return total;
  }
};
