#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  std::unordered_map<long, std::string> map;
  const int p = 31;
  const int m = 1e9 + 7;

 public:
  bool hasAllCodes(const string_view& s, int k) {
    return rolling_hash(s, k);
  }

  bool rolling_hash(const string_view& s, int k) {
    if (s.size() < k) return false;
    
    int need = 1 << k;
    std::unordered_set<long> seen;

    long roll = horner(s, k);
    seen.insert(roll);
    need--;

    long pow_rm = 1;
    for (size_t i = 1; i < k; ++i) pow_rm = (pow_rm * p) % m;

    for (size_t i = k; i < s.size(); ++i) {
      roll = (roll + m - pow_rm * s[i - k] % m) % m;
      roll = (roll * p + s[i]) % m;
      if (!seen.count(roll)) {
        seen.insert(roll);
        need--;
        if (need == 0) return true;
      }
    }

    return false;
  }

  bool rabin_karp(const string_view& s, int k) {
    if (s.size() < k) return false;

    // build all possible candidates
    std::string str;
    std::vector<long> vec;
    vec.push_back(0);
    backtrack(str, vec, k);

    long roll = horner(s, k);

    auto it = map.find(roll);
    if (it != map.end() && it->second == s.substr(0, k)) map.erase(roll);

    long pow_rm = 1;
    for (size_t i = 1; i < k; ++i) pow_rm = (pow_rm * p) % m;

    for (size_t i = k; i < s.size(); ++i) {
      roll = (roll + m - pow_rm * s[i - k] % m) % m;
      roll = (roll * p + s[i]) % m;
      auto it = map.find(roll);
      if (it != map.end() && it->second == s.substr(i - k + 1, k)) {
        map.erase(roll);
        if (map.empty()) return true;
      }
    }
    return map.empty();
  }

  long horner(const std::string_view& str, int k) {
    long hashed = 0;
    for (int i = 0; i < k; ++i) hashed = (hashed * p + str[i]) % m;
    return hashed;
  }

  void backtrack(std::string& stack, std::vector<long>& rolls, int k) {
    if (stack.size() == k) {
      map[rolls.back()] = stack;
      return;
    }

    for (char ch : {'0', '1'}) {
      stack.push_back(ch);
      rolls.push_back((rolls.back() * p + stack.back()) % m);
      backtrack(stack, rolls, k);
      stack.pop_back();
      rolls.pop_back();
    }
  }
};
