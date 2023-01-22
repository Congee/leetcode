#ifdef __LOCAL__
#include <leetcode.h>

// This is the HtmlParser's API interface.
// You should not implement it, or speculate about its implementation
class HtmlParser {
 public:
  vector<string> getUrls(string url);
};

#endif

class Solution {
 public:
  vector<string> crawl(string startUrl, HtmlParser parser) {
    // parse hostname
    // store urls crawled into a hashset
    // recursively crawl
    // trailing slash???
    //
    // in real world, use stacks for different domains, queues for each domain

    std::string valid_hostname = hostname_of(startUrl);
    std::vector<std::string> stack({startUrl});
    std::unordered_set<std::string> seen({startUrl});

    while (stack.size()) {
      auto&& urls = parser.getUrls(stack.back());
      stack.pop_back();
      for (auto&& url : urls) {
        if (hostname_of(url) != valid_hostname) continue;
        if (seen.count(url)) continue;

        stack.push_back(url);
        seen.insert(url);
      }
    }

    return std::vector<string>(seen.begin(), seen.end());
  }

  inline std::string hostname_of(const std::string& url) const {
    return url.substr(7, url.find_first_of('/', 7) - 7);
  }
};
