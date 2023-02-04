#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int findTheWinner(int n, int k) {
    // f(n,k) = (f(n-1,k) + k) % n;
    return recurse(n, k) + 1;  // 0 based to 1 based
  }

  int recurse(int n, int k) {
    if (n == 1) return 0;
    return (recurse(n - 1, k) + k) % n;
  }

  int simulate(int n, int k) {
    // simulate
    k -= 1;
    std::list<int> queue;
    for (int i = 0; i < n; ++i) queue.push_back(i);
    auto curr = queue.begin();

    while (queue.size() > 1) {
      int x = k % queue.size();

      auto to_end = std::distance(curr, queue.end());
      // 0 3 4 end;
      //   * k = 2
      //
      // 0 1 2 3 4 end
      //       *  k = 3
      if (to_end <= x)
        curr = std::next(queue.begin(), x - to_end);
      else
        curr = std::next(curr, x);

      auto next = std::next(curr);
      if (next == queue.end()) next = queue.begin();
      queue.erase(curr);
      curr = next;
    }

    return *queue.begin() + 1;
  }
};
