#ifdef __LOCAL__
#include <leetcode.h>
#endif

std::vector<std::string> split(const std::string& str, const std::string& pattern) {
    std::regex re{pattern};
    return {
        std::sregex_token_iterator(str.begin(), str.end(), re, -1),
        std::sregex_token_iterator()
    };
}


class Solution {
 public:
  string validIPAddress(const string& queryIP) {
    if (queryIP.empty()) return "Neither";
    if (queryIP.find('.') != std::string::npos) {
      auto vec = split(queryIP, "\\.");
      if (vec.size() != 4) return "Neither";
      if (queryIP.front() == '.' || queryIP.back() == '.') return "Neither";
      for (auto&& blk : vec) {
        // 0-255
        if (blk.empty() || blk.size() > 3) return "Neither";
        if (blk[0] == '0' && blk.size() > 1) return "Neither";
        for (char ch : blk) {
          if (!std::isdigit(ch)) return "Neither";
          // if (ch - '0' > 5) return "Neither";
        }

        auto number = std::stoi(blk);
        if (number > 255) return "Neither";
      }

      return "IPv4";
    }

    auto vec = split(queryIP, ":");
    if (vec.size() != 8) return "Neither";
    if (queryIP.front() == ':' || queryIP.back() == ':') return "Neither";

    for (auto&& blk : vec) {
      if (blk.size() < 1 || blk.size() > 4) return "Neither";

      for (char ch : blk) {
        // [0-9a-fA-F]
        auto yes = ('0' <= ch && ch <= '9') || ('a' <= ch && ch <= 'f') ||
                   ('A' <= ch && ch <= 'F');
        if (!yes) return "Neither";
      }

      // 0000-ffff
      auto number = std::stoi("0x" + blk);
      if (number > 0xffff) return "Neither";
    }

    return "IPv6";
  }
};
