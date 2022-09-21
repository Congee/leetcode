#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  int p = 31;
  int m = 1e9 + 7;

 public:
  bool differByOne(vector<string>& dict) {
    if (dict.size() <= 1) return false;
    // build hash tables for each position with of the dropped character
    int N = dict.size();
    int M = dict[0].size();

    std::vector<long> pows(M);
    pows[0] = 1;
    for (int i = 1; i < M; ++i) pows[i] = pows[i - 1] * p % m;

    auto hash = [&](const std::string& s) {
      long hashed = 0;
      for (size_t i = 0; i < s.size(); ++i)
        hashed = hashed + (s[i] - '`') * pows[i] % m;
      return hashed;
    };

    std::vector<long> hs(N);
    for (int i = 0; i < N; ++i)
      hs[i] = hash(dict[i]);

    for (int pos = 0; pos < M; ++pos) {
      // int pos = 2;
      std::unordered_set<long> seen;  // <hash, idx>
      for (int i = 0; i < N; ++i) {
        auto h = (hs[i] + m - (dict[i][pos] - '`') * pows[pos] % m) % m;
        if (seen.count(h)) return true;
        seen.insert(h);
      }
    }
    return false;
  }
};
