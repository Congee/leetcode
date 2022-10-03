#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int minimizeXor(int num1, int num2) {
    int num_bits = std::bitset<32>(num2).count();

    int ret = 0;

    int count = 0;
    for (int i = 0; i < 32 && count < num_bits; ++i) {
      if ((1 << (31 - i)) & num1) {
        count++;
        ret |= 1 << (31 - i);
      }
    }

    int rem = num_bits - count;
    for (int i = 0; i < 32 && rem; ++i) {
      if (((1 << i) & num1) == 0) {
        ret |= 1 << i;
        rem--;
      }
    }

    return ret;
  }
};
