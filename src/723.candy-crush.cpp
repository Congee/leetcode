#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  vector<vector<int>> candyCrush(vector<vector<int>>& board) {
    // it is too much code with two pointers
    // trade performance for clarity
    const int m = board.size(), n = board[0].size();

    std::unordered_set<int> crushable;

    auto search = [&]() {
      for (int r = 0; r < m; ++r) {
        for (int c = 0; c + 2 < n; ++c) {
          int curr = board[r][c];
          if (curr && curr == board[r][c + 1] && curr == board[r][c + 2]) {
            crushable.insert(r * n + c + 0);
            crushable.insert(r * n + c + 1);
            crushable.insert(r * n + c + 2);
          }
        }
      }

      for (int r = 0; r + 2 < m; ++r) {
        for (int c = 0; c < n; ++c) {
          int curr = board[r][c];
          if (curr && curr == board[r + 1][c] && curr == board[r + 2][c]) {
            crushable.insert((r + 0) * n + c);
            crushable.insert((r + 1) * n + c);
            crushable.insert((r + 2) * n + c);
          }
        }
      }
    };

    auto drop = [&]() {
      for (int c = 0; c < n; ++c) {
        int offset = 0;
        for (int r = m - 1; r >= 0; --r) {
          int k = r + offset;
          if (crushable.count(r * n + c))
            offset++;
          else
            board[k][c] = board[r][c];
        }

        for (int r = 0; r < offset; ++r) board[r][c] = 0;
      }
    };

    while (true) {  // unstable
      search();
      if (crushable.empty()) break;
      drop();
      crushable.clear();
    }

    return board;
  }
};
