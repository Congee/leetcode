#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  string strWithout3a3b(int a, int b) { return simple(a, b); }

  string simple(int a, int b) {
    std::string str;
    int conta = 0, contb = 0;
    while (a + b) {
      if ((a > b && conta < 2) || (a <= b && contb == 2)) {
        a--;
        str += 'a';
        conta++;
        contb = 0;

      } else {
        b--;
        str += 'b';
        contb++;
        conta = 0;
      }
      continue;

      // the above further simplifies the following

      if (a > b) {
        if (conta < 2) {
          a--;
          str += 'a';
          conta++;
          contb = 0;
        } else {
          b--;
          str += 'b';
          contb++;
          conta = 0;
        }
      } else if (b >= a) {
        if (contb < 2) {
          b--;
          str += 'b';
          contb++;
          conta = 0;
        } else {
          a--;
          str += 'a';
          conta++;
          contb = 0;
        }
      }
    }

    return str;
  }

  string naive(int a, int b) {
    std::string str;

    int continuous_a = 0, continuous_b = 0;
    while (a + b) {
      if (continuous_a == 2) {
        str += 'b';
        b--;
        continuous_a = 0;
        continuous_b = 1;
      } else if (continuous_b == 2) {
        str += 'a';
        a--;
        continuous_b = 0;
        continuous_a = 1;
      } else if (a - b > 2) {
        str += "aa";
        a -= 2;
        continuous_a += 2;
        continuous_b = 0;
      } else if (b - a > 2) {
        str += "bb";
        b -= 2;
        continuous_a = 0;
        continuous_b += 2;
      } else if (a > b) {
        str += 'a';
        a--;
        continuous_a++;
        continuous_b = 0;
      } else if (b > a) {
        str += 'b';
        b--;
        continuous_a = 0;
        continuous_b++;
      } else {
        str += 'a';
        a--;
        continuous_a++;
        continuous_b = 0;
      }
    }

    return str;
  }
};
