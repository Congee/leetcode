#ifdef __LOCAL__
#include <leetcode.h>
#endif

class NumMatrix {
  int m, n;
  std::vector<std::vector<long>> psum;

 public:
  NumMatrix(vector<vector<int>>& matrix) {
    m = matrix.size(), n = matrix[0].size();
    psum.resize(m + 1, std::vector<long>(n + 1));
    for (int r = 1; r <= m; ++r) {
      for (int c = 1; c <= n; ++c) {
        psum[r][c] = psum[r - 1][c] + psum[r][c - 1] - psum[r - 1][c - 1] +
                     matrix[r - 1][c - 1];
      }
    }
  }

  int sumRegion(int a, int b, int x, int y) {
    return psum[x + 1][y + 1] - psum[a][y + 1] - psum[x + 1][b] + psum[a][b];
  }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */
