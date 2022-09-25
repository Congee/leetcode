#ifdef __LOCAL__
#include <leetcode.h>
#endif

static const auto dirs = std::vector<std::pair<int, int>>{
  {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}};
class Solution {
  static const auto zero_to_one = 2;
  static const auto one_to_zero = 3;

 public:
  void gameOfLife(vector<vector<int>>& board) {
    int rows = board.size();
    int cols = board[0].size();
    auto is_valid = [&](int row, int col) {
      return row >= 0 && col >= 0 && row < rows && col < cols;
    };

    auto count_nbs = [&](int row, int col) {
      int count = 0;
      for (auto&& [dr, dc] : dirs) {
        row += dr;
        col += dc;
        if (is_valid(row, col)) {
          auto cell = board[row][col];
          if (cell == 1 || cell == one_to_zero) count++;
        }
      }
      return count;
    };

    for (int r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
        auto& cell = board[r][c];
        auto count = count_nbs(r, c);
        // 1.
        if ((cell == 1 || cell == one_to_zero) && count < 2)
          cell = one_to_zero;
        else if ((cell == 1 || cell == one_to_zero) && (count == 2 || count == 3))
          ;
        else if ((cell == 1 || cell == one_to_zero) && count > 3)
          cell = one_to_zero;
        else if ((cell == 0 || cell == zero_to_one) && count == 3)
          cell = zero_to_one;
      }
    }

    for (int r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
        auto& cell = board[r][c];
        if (cell == one_to_zero)
          cell = 0;
        else if (cell == zero_to_one)
          cell = 1;
      }
    }

    for (auto&& vec: board) {
      std::cout << vec << std::endl;
    }
  }
};
