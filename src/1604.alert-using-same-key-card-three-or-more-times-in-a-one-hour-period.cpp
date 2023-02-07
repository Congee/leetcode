#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  vector<string> alertNames(vector<string>& keyName, vector<string>& keyTime) {
    // rate limiting: fixed window counter
    std::unordered_map<std::string, std::vector<int>> map;
    int n = keyName.size();
    // three or MORE times
    // a single day: clear on entering a new day

    auto parse = [](const std::string& time) {
      auto hour = time.substr(0, 2);
      auto min = time.substr(3);
      return std::stoi(hour) * 60 + std::stoi(min);
    };

    for (int i = 0; i < n; ++i) map[keyName[i]].push_back(parse(keyTime[i]));

    std::vector<std::string> result;
    for (auto& [name, times] : map) {
      std::sort(times.begin(), times.end());

      for (size_t lo = 0, hi = 0; hi < times.size(); ++hi) {
        if (times[lo] + 60 < times[hi]) lo++;

        if (hi - lo >= 2) {
          result.push_back(name);
          break;
        }
      }
    }

    std::sort(result.begin(), result.end());
    return result;
  }
};
