#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  vector<int> platesBetweenCandles(string s, vector<vector<int>>& queries) {
    return record_candles(s, queries);
    return prefix_sum_optimized(s, queries);
  }

  vector<int> record_candles(string s, vector<vector<int>>& queries) {
    int n = s.size();
    std::vector<int> left_candle_indices(n, -1), right_candle_indices(n, -1),
      candles(n);
    for (int cnt = 0, left_candle = -1, right_candle = -1, i = 0; i < n; ++i) {
      int r = n - i - 1;
      if (s[i] == '|') {
        cnt++;
        left_candle = i;
      }
      if (s[r] == '|') {
        right_candle = r;
      }

      left_candle_indices[i] = left_candle;
      right_candle_indices[r] = right_candle;
      candles[i] = cnt;
    }
    if (candles.back() < 2) return std::vector<int>(queries.size());

    std::vector<int> result;
    for (auto&& query : queries) {
      int lo = right_candle_indices[query[0]],
          hi = left_candle_indices[query[1]];

      bool wrong = lo == -1 || hi == -1 || lo + 1 >= hi;
      result.push_back(wrong ? 0 : hi - lo - (candles[hi] - candles[lo]));
    }

    return result;
  }

  vector<int> prefix_sum_optimized(string s, vector<vector<int>>& queries) {
    // count number of plates between plates by manipulating candle indices
    int n = s.size();
    std::vector<int> candles;
    for (int i = 0; i < n; ++i) {
      if (s[i] == '|') candles.push_back(i);
    }
    if (candles.size() < 2) return std::vector<int>(queries.size());

    std::vector<int> result;
    // "***|**|*****|**||**|*"
    for (auto&& query : queries) {
      int lo = query[0], hi = query[1];
      auto it_left = std::lower_bound(candles.begin(), candles.end(), lo);
      if (it_left == candles.end() || *it_left >= hi) {
        result.push_back(0);
        continue;
      }

      auto it_right =
        std::prev(std::upper_bound(candles.begin(), candles.end(), hi));
      if (it_right == candles.begin() || *it_right <= lo || *it_right > hi) {
        result.push_back(0);
        continue;
      }
      result.push_back((*it_right - *it_left) - (it_right - it_left));
    }

    return result;
  }

  vector<int> prefix_sum(string s, vector<vector<int>>& queries) {
    // prefix sum with binary search
    // 1. use prefix sum to record all candles at each position
    // 2. use binary search to find candle positions in query
    // 3. use the positions above to calculate number of candles
    // 4. handle corner cases from the above two steps
    int n = s.size();
    std::vector<int> psum(n + 1);
    std::vector<int> candles;
    for (int i = 1; i < n + 1; ++i) {
      psum[i] = psum[i - 1] + (s[i - 1] == '*');
      if (s[i - 1] == '|') candles.push_back(i - 1);
    }
    if (candles.size() < 2) return std::vector<int>(queries.size());

    std::vector<int> result;
    // "***|**|*****|**||**|*"
    for (auto&& query : queries) {
      int lo = query[0], hi = query[1];
      auto it_left = std::lower_bound(candles.begin(), candles.end(), lo);
      if (it_left == candles.end() || *it_left >= hi) {
        result.push_back(0);
        continue;
      }

      auto it_right =
        std::prev(std::upper_bound(candles.begin(), candles.end(), hi));
      if (it_right == candles.begin() || *it_right <= lo || *it_right > hi) {
        result.push_back(0);
        continue;
      }
      result.push_back(psum[*it_right + 1] - psum[*it_left]);
    }

    return result;
  }
};
