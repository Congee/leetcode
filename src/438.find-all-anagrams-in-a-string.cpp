#ifdef __LOCAL__
#include <leetcode.h>
#endif

// comparing an array of size 26 runs faster than with a hashmap. O(n)*26
// actually finding 26 prime numbers then do rolling hash results int O(n)
class Solution {
 public:
  vector<int> findAnagrams(const std::string& s, const std::string& p) {
    if (s.size() < p.size()) return {};

    auto n = s.size();

    std::unordered_map<char, int> pmap;  // <char, count>
    for (auto ch : p) pmap[ch]++;

    std::unordered_map<char, int> smap;  // <char, count>
    for (size_t i = 0; i < p.size(); ++i) smap[s[i]]++;

    std::vector<int> vec;
    // abcde
    // ab
    for (size_t lo = 0, hi = p.size() - 1; lo < n - p.size(); ++lo, ++hi) {
      if (smap == pmap) vec.push_back(lo);
      smap[s[lo]]--;
      if (hi + 1 < n) smap[s[hi + 1]]++;
    }

    return vec;
  }
};
