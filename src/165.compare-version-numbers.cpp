#ifdef __LOCAL__
#include <leetcode.h>
#endif
#include <regex>

std::vector<std::string> split(const std::string& str, const std::string& pat) {
  std::regex re{pat};
  return {
    std::sregex_token_iterator(str.begin(), str.end(), re, -1),
    std::sregex_token_iterator()};
}

class Solution {
 public:
  int compareVersion(string& version1, string& version2) {
    auto v1 = split(version1, "\\.");
    auto v2 = split(version2, "\\.");
    int i = 0, j = 0;
    while (i < v1.size() && j < v2.size()) {
      auto rev1 = std::stoi(v1[i++]);
      auto rev2 = std::stoi(v2[j++]);
      if (rev1 < rev2) return -1;
      if (rev1 > rev2) return +1;
    }

    if (j < v2.size()) {
      while (j < v2.size()) {
        for (char ch : v2[j]) {
          if (ch != '.' && ch != '0') return -1;  // v2 longer & bigger
        }
        j++;
      }
      return 0;
    }

    if (i < v1.size()) {
      while (i < v1.size()) {
        for (char ch : v1[i]) {
          if (ch != '.' && ch != '0') return +1;  // v1 longer & bigger
        }
        i++;
      }
      return 0;
    }

    return 0;
  }
};
