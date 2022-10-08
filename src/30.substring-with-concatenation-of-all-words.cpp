#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  std::unordered_map<std::string_view, int> map;
  std::vector<int> vec;

 public:
  void window(const std::string_view& s, int start, vector<string>& words) {
    int n = s.size(), word_len = words[0].size();
    size_t matched_len = 0;
    std::unordered_map<std::string_view, int> ours;

    for (int lo = start, hi = start; hi < n - word_len + 1; hi += word_len) {
      auto sub = s.substr(hi, word_len);

      if (map.count(sub) == 0) {
        ours.clear();
        matched_len = 0;
        lo = hi + word_len;
        continue;
      }

      ours[sub]++;
      matched_len++;
      if (ours[sub] > map[sub]) {
        while (ours[sub] > map[sub]) {
          auto left_most = s.substr(lo, word_len);
          ours[left_most]--; if (ours[left_most] == 0) ours.erase(left_most);
          lo += word_len;

          matched_len--;
        }
      }

      if (matched_len == words.size()) vec.push_back(lo);
    }
  }

  vector<int> findSubstring(const string& s, vector<string>& words) {
    for (auto&& w : words) map[w]++;

    for (size_t i = 0; i < words[0].size(); ++i) window(s, i, words);
    return vec;
  }
};

// abcdeabc ["abc", "cde"]
class Slow : Solution {
 public:
  // bottom 5%
  vector<int> findSubstring(const string& s, vector<string>& words) {
    auto sv = std::string_view(s);
    const int wd = words[0].size();
    const auto len = wd * words.size();
    if (s.size() < len) return {};

    std::unordered_map<std::string_view, int> hs;
    for (auto&& w : words) hs[w]++;

    std::vector<int> vec;
    for (size_t i = 0; i < s.size() - wd + 1; ++i) {
      auto curr = sv.substr(i, wd);
      if (hs.count(curr)) {
        std::unordered_map<std::string_view, int> ours{{curr, 1}};

        for (size_t j = i + wd; j < i + len - wd + 1; j += wd) {
          auto wordj = sv.substr(j, wd);
          if (!hs.count(wordj)) break;
          ours[wordj]++;
        }

        if (ours == hs) vec.push_back(i);
      }
    }

    return vec;
  }
};

class TLE : Solution {
 public:
  vector<int> findSubstring(const string& s, vector<string>& words) {
    // replace every word
    const int wd = words[0].size();
    const int len = wd * words.size();
    if (s.size() < len) return {};

    const int p = 31;
    const int m = 1e9 + 7;
    std::vector<long> pows(len);
    pows[0] = 1;
    for (int i = 1; i < len; ++i) pows[i] = pows[i - 1] * p % m;

    std::unordered_set<long> hashes;
    std::sort(words.begin(), words.end());
    do {
      long hash = 0;
      for (int i = 0; i < len; ++i) {
        hash = (hash + (words[i / wd][i % wd] - '`') * pows[i] % m) % m;
      }
      hashes.insert(hash);

      // XXX: too slow here O(N!)
    } while (std::next_permutation(words.begin(), words.end()));

    std::vector<int> vec;
    long roll = 0;
    long pow_rm = 1;

    for (int i = s.size() - 1; i >= 0; --i) {
      roll = (roll * p + s[i] - '`') % m;

      // abcde
      //  bd
      if (i < s.size() - len)
        roll = (roll + m - (s[i + len] - '`') * pow_rm % m) % m;
      else
        pow_rm = (pow_rm * p) % m;

      if (hashes.count(roll)) vec.push_back(i);
    }

    return vec;
  }
};
