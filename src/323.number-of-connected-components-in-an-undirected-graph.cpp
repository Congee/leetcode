#ifdef __LOCAL__
#include <leetcode.h>
#endif

class UnionFind {
 private:
  std::vector<int> root;
  std::vector<int> rank;

 public:
  UnionFind(int n) : root(n), rank(n, 0) {
    for (int i = 0; i < n; ++i) root[i] = i;
  }

  int find(int x) {
    if (x == root[x]) return x;
    return root[x] = find(root[x]);
  }

  int connect(int x, int y) {
    auto root_x = find(x);
    auto root_y = find(y);

    if (root_x == root_y) return 0;

    if (rank[root_x] < rank[root_y])
      root[root_x] = root_y;
    else if (rank[root_x] > rank[root_y])
      root[root_y] = root_x;
    else {
      root[root_y] = root_x;
      rank[root_x]++;
    }
    return 1;
  }
};

class Solution {
 public:
  int countComponents(int n, vector<vector<int>>& edges) {
    UnionFind uf(n);

    for (auto& edge : edges) {
      n -= uf.connect(edge[0], edge[1]);
    }

    return n;
  }
};
