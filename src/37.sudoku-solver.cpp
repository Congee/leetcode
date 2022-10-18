#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  std::array<std::unordered_set<char>, 9> rows;
  std::array<std::unordered_set<char>, 9> cols;
  std::array<std::unordered_set<char>, 9> squares;
  vector<vector<char>> board;

 public:
  void solveSudoku(vector<vector<char>>& __board) {
    board = std::move(__board);

    for (int r = 0; r < 9; ++r) {
      for (int c = 0; c < 9; ++c) {
        char ch = board[r][c];
        if (ch != '.') {
          rows[r].insert(ch);
          cols[c].insert(ch);
          squares[(r / 3) * 3 + c / 3].insert(ch);
        }
      }
    }

    backtrack(0, 0);
    __board = std::move(board);
  }

  bool saw(int row, int col, char ch) {
    // 6, 6
    // 8, 8
    auto idx = (row / 3) * 3 + col / 3;
    return rows[row].count(ch) || cols[col].count(ch) || squares[idx].count(ch);
  }

  bool backtrack(int row, int col) {
    if (row == 8 && col == 9) return true;
    if (col == 9) {
      row++;
      col = 0;
    }

    if (board[row][col] != '.') return backtrack(row, col + 1);

    for (char ch : "123456789"s) {
      if (saw(row, col, ch)) continue;

      board[row][col] = ch;
      rows[row].insert(ch);
      cols[col].insert(ch);
      squares[(row / 3) * 3 + col / 3].insert(ch);

      if (backtrack(row, col + 1)) return true;

      board[row][col] = '.';
      rows[row].erase(ch);
      cols[col].erase(ch);
      squares[(row / 3) * 3 + col / 3].erase(ch);
    }

    return false;
  }
};
