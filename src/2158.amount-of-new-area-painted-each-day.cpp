#ifdef __LOCAL__
#include <leetcode.h>
#endif

struct Node {
  int lo, hi, sum;
  Node *left, *right;
  Node(int __lo, int __hi) : lo(__lo), hi(__hi) {}
};

class Solution {
  std::vector<int> tree;

 public:
  vector<int> amountPainted(vector<vector<int>>& paint) {
    return segment_tree(paint);
    return sweep_line(paint);
    return merge_intervals(paint);
    return jump_line(paint);
  }

  auto increment(int pos, int qlo, int qhi, int lo, int hi) -> int {
    int total = hi - lo + 1;

    if (tree[pos] == total) return 0;  // full

    if (qlo <= lo && lo <= hi && hi <= qhi) {  // full overlap
      int missing = total - tree[pos];
      tree[pos] = total;
      return missing;
    } else if (qlo > hi || qhi < lo)  // no overlap
      return 0;

    int mid = lo + (hi - lo) / 2;  // partial overlap
    int sum = increment(2 * pos + 1, qlo, qhi, lo, mid) +
              increment(2 * pos + 2, qlo, qhi, mid + 1, hi);
    tree[pos] += sum;
    return sum;
  };

  vector<int> segment_tree(vector<vector<int>>& paint) {
    int n = paint.size();
    int max_size = 0;
    for (int i = 0; i < n; ++i) max_size = std::max(max_size, paint[i][1]);

    tree.resize(max_size * 4);

    std::vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
      int qlo = paint[i][0], qhi = paint[i][1] - 1;
      vec[i] = increment(0, qlo, qhi, 0, max_size);
    }
    return vec;
  }

  vector<int> jump_line(vector<vector<int>>& paint) {
    // for each paint[i], count day by day
    // jump over already painted area
    int n = paint.size();
    std::vector<int> vec(n), lines(50001);
    for (int i = 0; i < n; ++i) {
      int start = paint[i][0], end = paint[i][1];
      while (start < end) {
        vec[i] += lines[start] == 0;
        int jump = std::max(start + 1, lines[start]);
        lines[start] = std::max(start, end);  // compression
        start = jump;
      }
    }

    return vec;
  }

  vector<int> sweep_line(vector<vector<int>>& paint) {
    int n = paint.size(), max_pos = 0;
    std::vector<std::tuple<int, int, int>> lines;  // <pos, idx, type>
    for (int i = 0; i < n; ++i) {
      lines.push_back({paint[i][0], i, -1});
      lines.push_back({paint[i][1], i, +1});
      max_pos = std::max(max_pos, paint[i][1]);
    }
    std::sort(lines.begin(), lines.end());

    std::set<int> indices;
    std::vector<int> vec(n);
    int prev = 0;
    for (auto&& [pos, idx, type] : lines) {
      if (indices.size()) vec[*indices.begin()] += pos - prev;
      prev = pos;
      type == -1 ? indices.insert(idx).second : indices.erase(idx);
    }

    return vec;
  }

  vector<int> merge_intervals(vector<vector<int>>& paint) {
    int n = paint.size();
    std::vector<int> vec(n, 0);
    std::map<int, int> tree;  // <l, r>; no overlaps exist in tree

    for (int i = 0; i < n; ++i) {
      int l = paint[i][0], r = paint[i][1];
      auto next = tree.upper_bound(l), curr = next;

      //   ------
      // ----  ---
      if (next != tree.begin() && std::prev(next)->second >= l)
        l = (--curr)->second;
      else
        curr = tree.insert({l, r}).first;

      int pt = r - l;

      while (next != tree.end() && next->first < r) {
        pt -= std::min(r, next->second) - next->first;
        r = std::max(r, next->second);
        tree.erase(next++);
      }
      curr->second = std::max(curr->second, r);
      vec[i] = std::max(0, pt);
    }

    return vec;
  }
};
