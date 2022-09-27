#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  std::unordered_map<std::string, std::string> root;
  std::unordered_map<std::string, int> rank;

  const std::string& find(const std::string& x) {
    if (x == root[x]) return x;
    return root[x] = find(root[x]);
  }

  void connect(const std::string& x, const std::string& y) {
    auto root_x = find(x);
    auto root_y = find(y);

    if (root_x == root_y) return;

    if (rank[root_x] < rank[root_y]) {
      root[root_x] = root_y;
    } else if (rank[root_x] > rank[root_y]) {
      root[root_y] = root_x;
    } else {
      root[root_y] = root_x;
      rank[root_x]++;
    }
  }

 public:
  bool areSentencesSimilarTwo(
    vector<string>& sentence1, vector<string>& sentence2,
    vector<vector<string>>& similarPairs
  ) {
    if (sentence1.size() != sentence2.size()) return false;

    for (auto&& pair : similarPairs) {
      root[pair[0]] = pair[0];
      root[pair[1]] = pair[0];
      rank[pair[0]] = 1;
      rank[pair[1]] = 0;
    }

    for (auto&& pair : similarPairs) {
      connect(pair[0], pair[1]);
    }

    int n = sentence1.size();
    for (int i = 0; i < n; ++i) {
      if (sentence1[i] == sentence2[i]) continue;
      if (root.count(sentence1[i]) == 0 || root.count(sentence2[i]) == 0)
        return false;
      if (find(sentence1[i]) == find(sentence2[i])) continue;

      return false;
    }

    return true;
  }
};
