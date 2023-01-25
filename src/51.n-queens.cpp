#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  int n, rows, cols, diags, antis;  // memo
  // actually we can directly initialize a baord and do 'Q' on push, '.' on pop
  std::vector<int> stack;
  std::vector<std::vector<std::string>> result;

 public:
  vector<vector<string>> solveNQueens(int __n) {
    n = __n;
    dfs(0);
    return result;
  }

  void dfs(int row) {
    if (row == n) return push_path();
    // diag => anti  starting from 1
    // (row, col) => (col, row) => col + (n - 1) - row

    for (int col = 0; col < n; ++col) {
      /// no need to check row as we go from top to bottom
      if (cols & (1 << col)) continue;
      if (diags & (1 << (row + col))) continue;
      if (antis & (1 << (col + (n - 1) - row))) continue;

      rows |= 1 << row;
      cols |= 1 << col;
      diags |= 1 << (row + col);
      antis |= 1 << (col + (n - 1) - row);
      stack.push_back(1 << col);

      dfs(row + 1);

      rows ^= 1 << row;
      cols ^= 1 << col;
      diags ^= (1 << (row + col));
      antis ^= 1 << (col + (n - 1) - row);
      stack.pop_back();
    }
  }

  void push_path() {
    std::vector<std::string> vec;
    for (int row : stack) {
      std::string str(n, '.');
      str[__builtin_ffs(row) - 1] = 'Q';
      vec.push_back(str);
    }
    result.push_back(vec);
  }
};
