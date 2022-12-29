#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  std::vector<int> root;
  std::vector<int> rank;
  int find(int x) {
    if (root[x] == x) return x;
    return root[x] = find(root[x]);
  }

  void connect(int x, int y) {
    int root_x = find(x);
    int root_y = find(y);

    if (root_x == root_y) return;

    if (rank[root_x] < rank[root_y])
      root[root_x] = root_y;
    else if (rank[root_x] > rank[root_y])
      root[root_y] = root_x;
    else {
      root[root_x] = root_y;
      rank[root_y]++;
    }
  }

 public:
  int numSimilarGroups(vector<string>& strs) {
    int n = strs.size();
    root.resize(n);
    rank.resize(n);
    std::iota(root.begin(), root.end(), 0);
    std::fill_n(rank.begin(), n, 0);

    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        if (are_similar(strs[i], strs[j])) connect(i, j);
      }
    }

    for (int i = 0; i < n; ++i) find(i);
    return std::unordered_set<int>(root.begin(), root.end()).size();
  }

  bool are_similar(const std::string& foo, const std::string& bar) {
    assert(foo.size() == bar.size());

    int diff = 0;
    for (int i = 0; i < foo.size(); ++i) {
      diff += foo[i] != bar[i];
      if (diff > 2) return false;
    }

    return diff == 0 || diff == 2;
  }
};
