#ifdef __LOCAL__
#include <leetcode.h>
#endif

using Pair = std::pair<std::string, std::string>;

class Solution {
 public:
  vector<string> reorderLogFiles(vector<string>& logs) {
    // NOTE: std::string_view or std::string::compare offer better performance
    // Those are zero-copy abstraction
    //
    // <identifier, type, content>
    std::vector<Pair> letter_logs;
    std::vector<std::string> digit_logs;
    for (auto&& log : logs) {
      auto pos = log.find_first_of(' ');
      bool is_digit = std::isdigit(log[pos + 1]);
      if (is_digit)
        digit_logs.push_back(log);
      else
        letter_logs.emplace_back(
          std::string(log.begin(), log.begin() + pos),
          std::string(log.begin() + pos + 1, log.end())
        );
    }
    std::sort(
      letter_logs.begin(),
      letter_logs.end(),
      [&](const Pair& lhs, const Pair& rhs) {
        int cmp = lhs.second.compare(rhs.second);
        if (cmp == 0)
          return lhs.first < rhs.first;
        else
          return cmp < 0;
      }
    );

    std::vector<std::string> result;
    for (auto&& [ident, content] : letter_logs)
      result.push_back({ident + " " + content});

    result.insert(result.end(), digit_logs.begin(), digit_logs.end());

    return result;
  }
};
