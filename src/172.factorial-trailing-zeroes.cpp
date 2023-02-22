#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  std::pair<int, int> times(int n, int div) {
    int count = 0;
    while (n % div == 0) {
      n /= div;
      count++;
    }

    return {count, n};
  }

  int trailingZeroes(int n) {
    return smart(n);
    return count_5s(n);
    return naive(n);
  }

  int smart(int n) {
    // n/5 + n/25 + n/125 + n/625 + ...
#if 0
    int count = 0, power = 5;
    while (n >= power) {
      count += n / power;
      power *= 5;
    }
#endif

    // or, equivalent
    int count = 0;
    while (n) {
      n /= 5;
      count += n;
    }

    return count;
  }

  int count_5s(int n) {
    // on top of the idea of getting std::min(count2, count5) + count10;
    // a key observation is for every factor of 5, a 2 appears before it.
    // just count 5s;

    int count = 0;
    for (int x = 5; x <= n; ++x) {
      int power = 5;  // 5, 25, 125, 625
      while (x % power == 0) {
        count++;
        power *= 5;
      }

      continue;

      // or, equivalent
      int rem = x;
      while (rem % 5 == 0) {
        count++;
        rem /= 5;
      }
    }

    return count;
  }

  int naive(int n) {
    int count2 = 0, count5 = 0, count10 = 0;

    // 5 20 -> 100 -> 2
    for (int x = 2; x <= n; ++x) {
      if (!(x % 2 == 0 || x % 5 == 0)) continue;

      auto [count, rem] = times(x, 10);
      count10 += count;

      std::tie(count, rem) = times(rem, 5);
      count5 += count;

      count2 += __builtin_ctz(rem);
    }

    return count10 + std::min(count2, count5);
  }
};
