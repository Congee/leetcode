#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  vector<vector<long long>> splitPainting(vector<vector<int>>& segments) {
    // -------
    // -------
    //        -------
    // ----------
    return sweep_psum(segments);
    return sweep(segments);
  }

  vector<vector<long long>> sweep_psum(vector<vector<int>>& segments) {
    std::unordered_set<int> ends;
    int n = 100002;
    std::vector<long> psum(n, 0);
    for (auto&& seg : segments) {
      psum[seg[0]] += seg[2];
      psum[seg[1]] -= seg[2];
      ends.insert(seg[0]);
      ends.insert(seg[1]);
    }

    vector<vector<long long>> vec;
    long long sum = 0, prev_idx = 0;
    for (int i = 1; i < n; ++i) {
      if (sum > 0 && ends.count(i)) vec.push_back({prev_idx, i, sum});

      sum += psum[i];
      prev_idx = ends.count(i) ? i : prev_idx;
    }

    return vec;
  }

  vector<vector<long long>> sweep(vector<vector<int>>& segments) {
    std::vector<std::tuple<int, int, int>> lines;  // <pos, type>

    for (auto&& seg : segments) {
      lines.push_back({seg[0], +1, seg[2]});
      lines.push_back({seg[1], -1, seg[2]});
    }

    std::sort(lines.begin(), lines.end());

    vector<vector<long long>> vec;
    long long curr_sum = 0;
    for (int i = 0; i < lines.size(); ++i) {
      auto&& [pos, type, color] = lines[i];
      curr_sum += type * color;

      if (vec.size() && type == -1) {
        vec.back()[1] = pos;
        vec.back()[2] = std::max(curr_sum, vec.back().back());

        if (curr_sum > 0) {
          bool skip = false;
          if (i + 1 < lines.size()) {
            auto [nxt_pos, nxt_type, _] = lines[i + 1];
            if (nxt_pos == pos && nxt_type == type) skip = true;
          }

          if (!skip) vec.push_back({pos, -1, curr_sum});
        }
      }

      if (type == 1) {
        if (vec.size() && vec.back()[0] == pos && vec.back()[1] == -1) {
          vec.back()[2] = std::max(vec.back()[2], curr_sum);
        } else if (vec.size() && vec.back()[1] == -1) {
          vec.back()[1] = pos;
          vec.push_back({pos, -1, curr_sum});
        } else
          vec.push_back({pos, -1, curr_sum});
      }
    }
    return vec;
  }
};
