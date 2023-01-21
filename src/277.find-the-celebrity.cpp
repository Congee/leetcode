/* The knows API is defined for you.
      bool knows(int a, int b); */

#ifdef __LOCAL__
#include <leetcode.h>
bool knows(int a, int b);
#endif

class Solution {
 public:
  int findCelebrity(int n) {
    return by_buckets(n);
    return simulate(n);
    // another approach is to draw out the graph in 0-1 matrix
    //   0 1 2
    // 0 1 1 0
    // 1 0 1 0  -> *
    // 2 1 1 1
    // now find the point who colum has all 1s, col has only 1 1
  }

  int by_buckets(int n) {
    // I had this idea, but couldn't put it into code
    std::vector<int> stack(n);
    std::iota(stack.begin(), stack.end(), 0);

    while (stack.size() > 1) {
      // clang-format off
      int a = stack.back(); stack.pop_back();
      int b = stack.back(); stack.pop_back();
      // clang-format on

      stack.push_back(knows(a, b) ? b : a);
    }

    int c = stack.back();
    for (int i = 0; i < n; ++i) {
      if (i == c) continue;
      if (knows(c, i) || !knows(i, c)) return -1;
    }

    return c;
  }

  int simulate(int n) {
    // instead of determining who is a celebrity, try rule out who aren't
    int candidate = 0;
    for (int i = 1; i < n; ++i)
      if (knows(candidate, i)) candidate = i;

    for (int i = 0; i < n; ++i) {
      if (i == candidate) continue;
      // remember to cache the `knows` call in real world if it's expensive
      if (knows(candidate, i) || !(knows(i, candidate))) return -1;
    }

    return candidate;
  }

  int naive_topo_sort(int n) {
    // [1,1,0]
    // [0,1,0]
    // [1,1,1]
    // topological sort
    // the celebrity shall have indegree of n - 1
    std::vector<int> indegrees(n), outdegrees(n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (i == j) continue;
        if (knows(i, j)) {
          indegrees[j]++;
          outdegrees[i]++;
        }
      }
    }

    for (int i = 0; i < n; ++i)
      if (indegrees[i] == n - 1 && outdegrees[i] == 0) return i;

    return -1;
  }
};
