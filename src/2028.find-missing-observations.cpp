#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  vector<int> missingRolls(vector<int>& rolls, int mean, int n) {
    // (sumn + sumn) / (m + n) == mean; => sumn = (m + n) * mean - summ
    //
    // upper bound O(6^N)
    // pruning, every draw shall be <= n
    // sumn = 8, n = 3 => [1,1,6]; 8 % 6 == 2 == 3 - 1
    // sumn = 9, n = 3 => [1,2,6]; 9 % 6 == 3 == 3 - 0

    int summ = std::accumulate(rolls.begin(), rolls.end(), 0);
    int sumn = (rolls.size() + n) * mean - summ;
    if (sumn < n || sumn > n * 6) return {};

    return fill_by_avg(sumn, n);
    return fill_max_leading(sumn, n);
  }

  vector<int> fill_by_avg(int sumn, int n) {
    int rem = sumn % n;

    // 17, 3
    // [6,6,5]

    if (rem == 0) return std::vector<int>(n, sumn / n);

    std::vector<int> vec;
    vec.insert(vec.end(), rem, sumn / n + 1);
    vec.insert(vec.end(), n - rem, sumn / n);

    return vec;
  }

  vector<int> fill_max_leading(int sumn, int n) {
    // rolls = [1,5,6], mean = 3, n = 4
    // => [2,3,2,2]  9 4
    // => [6,1,1,1]
    //
    // => [2,1,1,1]  5 4
    // 4 * 1 + 1
    //
    // 5 % 4 = 1
    // 24 % 4 = 0
    //
    // 23 % 4 = 3, 5
    // [6 6 6 5]
    //
    // 18 % 4 = 2, 4
    // [6 6 3 3]
    //
    // 5 % 4 = 1, 1
    // [2 1 1 1];
    // 5 - 3 = 2 > 0
    // 3 => 1 1 1
    // avg = sumn / n
    // rem = sumn % n

    std::vector<int> vec;

    while (sumn && sumn >= n) {
      if (sumn == n) {
        vec.insert(vec.end(), n, 1);
        break;
      }

      int choice = std::min(sumn - (n - 1), 6);
      vec.push_back(choice);
      sumn -= choice;
      n--;
    }

    return vec;
  }
};
