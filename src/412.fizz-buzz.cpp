#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  vector<string> fizzBuzz(int n) {
    std::vector<std::string> vec(n);

    for (int i = 0; i < n; ++i) {
      auto curr = i + 1;
      if (curr % 15 == 0)
        vec[i] = "FizzBuzz";
      else if (curr % 3 == 0)
        vec[i] = "Fizz";
      else if (curr % 5 == 0)
        vec[i] = "Buzz";
      else
        vec[i] = std::to_string(curr);
    }

    return vec;
  }
};
