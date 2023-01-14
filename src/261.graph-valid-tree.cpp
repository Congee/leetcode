#ifdef __LOCAL__
#include <leetcode.h>
#endif

class UnionFind {
 private:
  std::vector<int> root;
  std::vector<int> rank;

 public:
  UnionFind(int size) : root(size), rank(size, 0) {
    for (int i = 0; i < size; ++i) {
      root[i] = i;
    }
  }

  int compress(int x) {
    if (x == root[x]) return x;
    return root[x] = compress(root[x]);
  }

  int find(int x) {
    while (x != root[x]) x = root[x];
    return x;
  }

  bool connect(int x, int y) {
    auto root_x = find(x);
    auto root_y = find(y);

    if (root_x == root_y) return false;

    if (rank[root_x] < rank[root_y])
      root[root_x] = root_y;
    else if (rank[root_x] > rank[root_y])
      root[root_y] = root_x;
    else {
      root[root_x] = root_y;
      rank[root_y]++;
    }
    return true;
  }

  bool is_tree() {
    for (int i = 0; i < root.size(); ++i) compress(i);
    return std::all_of(root.begin(), root.end(), [&](int x) {
      return x == *root.begin();
    });
  }
};

class Solution {
 public:
  bool validTree(int n, vector<vector<int>>& edges) {
    UnionFind uf(n);
    for (auto& edge : edges) {
      if (!uf.connect(edge[0], edge[1])) return false;
    }
    return uf.is_tree();
  }
};
