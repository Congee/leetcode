#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int minMoves(vector<int>& nums, int limit) {
    // [4,2,3,1]  4   -> 0
    // [100,0]    10  -> 2
    // [100,0]    100 -> 1
    // [1,100,0,1]

    // [1,2,4,3] limit = 4  range=[2, 8]
    // [1,3] -> 1 + 1 <= T < 4
    //          4 < T <  3+4
    //          1 + 3 == T
    //          3 + 4 <  T <= 8
    //
    // [2,4] -> 2 + 1 <= T < 2 + 4
    //          2 + 4 <  T < 4  + 4
    //          2 + 4 == T
    //          4 + 4 <  T <= 2 * 4  (x)
    //
    // 5 cases to find the optimal target sum T in [2, 2 * limit]
    // 2 <= T < min(A, B) + 1;               2;  2 <= 2 < (4, 5) + 1;
    // min(A, B) + 1 <= T < A + B;           1;  min(1, 3) + 1 <= 3 < 1 + 3
    // T = A + B;                            0;  2 = 1 + 1
    // A + B < T < max(A, B) + limit;        1;  1 + 2 < 4 < max(1, 2) + 4
    // max(A, B) + limit < T <= 2 * limit;   2;  max(1, 2) + 5 < 7 <= 2 * 5

    std::vector<int> delta(2 * limit + 2, 0);
    for (int i = 0, n = nums.size(); i < n / 2; ++i) {
      int l = nums[i], r = nums[n - i - 1];

      // sweep line on boundaries
      // translating ranges from:
      // [ 2, min(A+B)+1, A+B, A+B+1, max(A,B)+limit+1, 2*limit ]
      // delta[2]+=2,           delta[min(A,B)+1]        -=2
      // delta[min(A,B)+1] +=1, delta[A+B]               -=1
      // delta[A+B] +=0,        delta[A+B+1]             -=0
      // delta[A+B+1] +=1,      delta[max(A,B)+limit+1)] -=1
      // delta[max(A,B)+limit+1)]                        +=2
      // into:
      delta[2] += 2;
      delta[min(l, r) + 1]--;          // left
      delta[l + r]--;                  // left
      delta[l + r + 1]++;              // right
      delta[max(l, r) + limit + 1]++;  // right
    }

    int best = 2 * nums.size(), curr = 0;
    for (int i = 2; i <= 2 * limit; ++i) {
      curr += delta[i];
      best = std::min(best, curr);
    }
    return best;
  }
};
