#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  vector<string> subdomainVisits(vector<string>& cpdomains) {
    // trie or suffix hashmap
    std::unordered_map<std::string, int> map;

    for (auto&& cpdomain : cpdomains) {
      size_t i = 0;
      while (!std::isspace(cpdomain[i]))
        i++;
      size_t count = std::stoi(cpdomain.substr(0, i));
      cpdomain[i] = '.';

      for (; i < cpdomain.size(); ++i) {
        if (cpdomain[i] == '.') {
          // .com
          map[cpdomain.substr(i + 1, cpdomain.size() - i - 1)] += count;
        }
      }
    }

    std::vector<std::string> vec;
    for (auto&& [domain, cnt] : map)
      vec.push_back(std::to_string(cnt) + " " + domain);
    return vec;
  }
};
