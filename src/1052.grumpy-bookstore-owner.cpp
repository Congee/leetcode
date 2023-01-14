#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
    return two_pointers(customers, grumpy, minutes);
    return prefix_sum(customers, grumpy, minutes);
  }

  int two_pointers(vector<int>& customers, vector<int>& grumpy, int minutes) {
    // compared to the prefix sum approach, the state can be compressed if sum
    // around pointers.
    // sum all the regular satisifaction
    // maintain a sliding window that the owner can employ the secret
    // 0 0 0 0 0 0
    //       x x x
    int n = customers.size(), sum_zeros = 0, bonus = 0, max_bonus = 0;
    for (int i = 0; i < n; ++i) {
      if (grumpy[i] == 0)
        sum_zeros += customers[i];
      else
        bonus += customers[i];

      if (i - minutes >= 0 && grumpy[i - minutes] == 1)
        bonus -= customers[i - minutes];

      max_bonus = std::max(max_bonus, bonus);
    }

    return sum_zeros + max_bonus;
  }

  int prefix_sum(vector<int>& customers, vector<int>& grumpy, int minutes) {
    // [1,0,1,2,1,1,7,5]
    // [0,1,0,1,0,1,0,1]
    //      * * *

    // use two prefix sums, one for total regardless of emotion, the other of
    int n = grumpy.size();
    std::vector<int> psum_total(n + 1), psum_emo(n + 1);
    for (int i = 1; i <= n; ++i) {
      psum_total[i] = psum_total[i - 1] + customers[i - 1];
      psum_emo[i] = psum_emo[i - 1] + customers[i - 1] * (grumpy[i - 1] ^ 1);
    }

    int max = 0;
    for (int i = 0; i + minutes <= n; ++i) {
      int happy = psum_total[i + minutes] - psum_total[i];
      int curr = psum_emo[i] + psum_emo[n] - psum_emo[i + minutes] + happy;
      max = std::max(max, curr);
    }

    return max;
  }
};
