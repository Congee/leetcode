#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int minMutation(string& startGene, string& endGene, vector<string>& bank) {
    // bfs + Trie

    if (startGene == endGene) return 0;

    auto map = [](char nucleo) -> std::string {
      switch (nucleo) {
        case 'A': return std::string{'C', 'G', 'T'};
        case 'C': return std::string{'A', 'G', 'T'};
        case 'T': return std::string{'C', 'G', 'A'};
        case 'G': return std::string{'C', 'A', 'T'};
        default: __builtin_unreachable();
      }
    };

    std::unordered_set<std::string> mybank(bank.begin(), bank.end());
    std::unordered_set<std::string> seen({startGene});

    auto neighbors_of = [&](std::string& str) {
      std::vector<std::string> vec;
      for (char& ch : str) {
        char origin = ch;
        for (char to : map(ch)) {
          ch = to;
          if (mybank.count(str)) vec.push_back(str);
        }
        ch = origin;
      }

      return vec;
    };

    std::queue<std::string> queue({startGene});
    int steps = 0;
    while (queue.size()) {
      const int size = queue.size();
      steps++;
      for (int i = 0; i < size; ++i) {
        auto curr = queue.front();
        queue.pop();

        for (auto&& nb : neighbors_of(curr)) {
          if (nb == endGene) return steps;
          if (seen.count(nb)) continue;
          queue.push(nb);
          seen.insert(nb);
        }
      }
    }

    return -1;
  }
};
