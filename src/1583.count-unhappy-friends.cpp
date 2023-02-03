#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int unhappyFriends(
    int n, vector<vector<int>>& preferences, vector<vector<int>>& pairs
  ) {
    // because paris.length == 2, there is no chainning

    std::unordered_map<int, int> friends;
    for (auto&& pair : pairs) {
      int x = pair[0], y = pair[1];
      friends[x] = y;
      friends[y] = x;
    }

    // [[1,3,2],[2,3,0],[1,0,3],[1,0,2]]
    // 0        1       2       3
    std::vector<std::vector<int>> prefs(n, std::vector<int>(n, -1));
    for (int i = 0; i < n; ++i) {
      auto&& vec = preferences[i];
      for (int j = 0; j < n - 1; ++j) {
        prefs[i][vec[j]] = j;
      }
    }

    auto is_unhappy = [&](int x, int y) -> bool {
      for (int i = 0; i < prefs[x][y]; ++i) {
        int u = preferences[x][i];
        int v = friends[u];
        if (prefs[u][x] < prefs[u][v]) return true;
      }

      return false;
    };

    int unhappy = 0;
    for (auto&& pair : pairs) {
      int x = pair[0], y = pair[1];
      // prefs[x] = [u,u,u, y, _]
      // prefs[u] = [x,x,x, v, _]
      unhappy += is_unhappy(x, y);
      unhappy += is_unhappy(y, x);
    }

    return unhappy;
  }
};
