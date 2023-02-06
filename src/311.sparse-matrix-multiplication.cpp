#ifdef __LOCAL__
#include <leetcode.h>
#endif

using vv = vector<vector<int>>;
using Pair = std::pair<int, int>;

class SparseMatrix {
  const int nrow, ncol;
  vector<vector<Pair>> rows;

 public:
  SparseMatrix(const vv& dense)
    : nrow(dense.size()), ncol(dense[0].size()), rows(nrow) {
    for (int r = 0; r < nrow; ++r) {
      for (int c = 0; c < ncol; ++c) {
        if (dense[r][c]) rows[r].emplace_back(c, dense[r][c]);
      }
    }
  }

  vv multiply(const SparseMatrix& other) {
    vv result(nrow, vector<int>(other.ncol));
    //  +----------------+-+-+
    //  |                | | |
    //  +                + + +
    //  1 0 0   7 0 0    7 0 0
    // -1 0 3 * 0 0 0 = -7 0 3
    //          0 0 1
    //
    // [[(0,1)],            [[(0,7)],
    //  [(0,-1),(2,3)]]  *   [(2,1)]]
    for (int r = 0; r < nrow; ++r) {
      for (auto [c1, v1] : rows[r]) {
        for (auto [c2, v2] : other.rows[c1]) {
          result[r][c2] += v1 * v2;
        }
      }
    }

    return result;
  }
};

class Solution {
 public:
  vv multiply(vv& mat1, vv& mat2) {
    // what really costs is interaction with disk and memory
    return SparseMatrix(mat1).multiply(SparseMatrix(mat2));
    return two_pointers(mat1, mat2);
  }

  vv two_pointers(vv& mat1, vv& mat2) {
    std::vector<std::vector<std::pair<int, int>>> sparse1;
    for (size_t r = 0; r < mat1.size(); ++r) {
      std::vector<std::pair<int, int>> sparse_row;
      for (size_t c = 0; c < mat1[0].size(); ++c) {
        if (mat1[r][c] == 0) continue;
        sparse_row.push_back({c, mat1[r][c]});
      }

      sparse1.push_back(sparse_row);
    }

    std::vector<std::vector<std::pair<int, int>>> sparse2;
    for (size_t c = 0; c < mat2[0].size(); ++c) {
      std::vector<Pair> sparse_col;
      for (size_t r = 0; r < mat2.size(); ++r) {
        if (mat2[r][c] == 0) continue;
        sparse_col.push_back({r, mat2[r][c]});
      }
      sparse2.push_back(sparse_col);
    }

    vv result(mat1.size(), std::vector<int>(mat2[0].size()));
    for (size_t r1 = 0; r1 < sparse1.size(); ++r1) {
      for (size_t c2 = 0; c2 < sparse2.size(); ++c2) {
        // vector dot-product
        size_t i1 = 0, i2 = 0;
        auto vec1 = sparse1[r1], vec2 = sparse2[c2];
        while (i1 < vec1.size() && i2 < vec2.size()) {
          auto idx1 = vec1[i1].first, idx2 = vec2[i2].first;
          if (idx1 == idx2) {
            result[r1][idx1] += vec1[i1].second * vec2[i2].second;
            i1++;
            i2++;
          } else if (idx1 < idx2) {
            i1++;
          } else {
            i2++;
          }
        }
      }
    }

    return result;
  }
};
