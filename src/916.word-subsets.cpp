#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  // ["apple",  "google","leetcode"]
  //            ["o","le"]
  //            ["o","el"]
  //
  // ["amazon","apple","facebook","google","leetcode"]↩ ["lo","eo"]
  // ["google","leetcode"]
  vector<string> wordSubsets(vector<string>& words1, vector<string>& words2) {
    std::array<char, 26> map2 = {};
    for (auto&& w : words2) {
      std::array<char, 26> curr = {};
      for (char ch : w) {
        auto idx = ch - 'a';
        curr[idx]++;
        if (curr[idx] > map2[idx]) map2[idx] = curr[idx];
      }
    }

    std::vector<std::string> vec;

    std::array<char, 26> map1 = {};
    for (auto&& word : words1) {
      for (char ch : word) map1[ch - 'a']++;

      bool is_superset = true;
      for (int i = 0; i < 26; ++i) {
        if (map1[i] < map2[i]) {
          is_superset = false;
          break;
        }
      }

      if (is_superset) vec.push_back(word);

      map1 = {};
    }

    return vec;
  }
};
