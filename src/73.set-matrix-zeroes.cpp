#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  void setZeroes(vector<vector<int>>& matrix) { by_1st_row_with_zero(matrix); }

  void by_1st_row_with_zero(vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    int row_mem = -1;
    for (int r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
        if (matrix[r][c] == 0) {
          row_mem = r;
          goto out;
        }
      }
    }

  out:
    if (row_mem == -1) return;

    auto& mem = matrix[row_mem];

    for (int c = 0; c < cols; ++c) {
      auto& cell = mem[c];
      if (cell == 0)
        cell = 1;
      else
        cell = 0;
    }

    for (int r = 0; r < rows; ++r) {
      bool has_0 = false;
      for (int c = 0; c < cols; ++c) {
        if (r == row_mem) continue;

        auto& cell = matrix[r][c];
        if (cell == 0) {
          mem[c] = 1;
          has_0 = true;
        }
      }
      if (has_0) std::fill(matrix[r].begin(), matrix[r].end(), 0);
    }

    for (int c = 0; c < cols; ++c) {
      if (mem[c] == 1) {
        for (int r = 0; r < rows; ++r) {
          matrix[r][c] = 0;
        }
      }
    }

    std::fill(mem.begin(), mem.end(), 0);
  }

  void by_remember_cols(vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    std::unordered_set<int> cols_to_0;
    for (int r = 0; r < rows; ++r) {
      bool has_0 = false;
      for (int c = 0; c < cols; ++c) {
        if (matrix[r][c] == 0) {
          has_0 = true;
          cols_to_0.insert(c);
        }
      }
      if (has_0) std::fill(matrix[r].begin(), matrix[r].end(), 0);
    }

    for (auto c : cols_to_0) {
      for (int r = 0; r < rows; ++r) {
        matrix[r][c] = 0;
      }
    }
  }
};
