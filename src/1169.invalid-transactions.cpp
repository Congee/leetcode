#ifdef __LOCAL__
#include <leetcode.h>
#endif

struct Event {
  std::string name;
  int time;
  int amount;
  std::string location;
  int idx;
};

std::vector<std::string> split(const std::string& str, const std::string& pat) {
  std::regex re{pat};
  return {
    std::sregex_token_iterator(str.begin(), str.end(), re, -1),
    std::sregex_token_iterator()};
}

class Solution {
 public:
  vector<string> invalidTransactions(vector<string>& transactions) {
    int n = transactions.size();
    std::unordered_map<int, std::unordered_map<std::string, std::vector<Event>>>
      map;
    std::unordered_set<int> invalid_indices;
    std::vector<std::string> result;
    std::vector<Event> events(n);

    for (int i = 0; i < n; ++i) {
      auto&& vec = split(transactions[i], ",");
      auto curr = Event{
        vec[0], std::stoi(vec[1]), std::stoi(vec[2]), vec[3], i};
      map[curr.time][curr.name].push_back(curr);
      events[i] = curr;
    }

    for (auto&& curr : events) {
      if (curr.amount > 1000) invalid_indices.insert(curr.idx);
      // not 1 - 60; dumb yeah
      for (int past = std::max(0, curr.time - 60); past <= curr.time; ++past) {
        for (auto&& ev : map[past][curr.name]) {
          if (ev.location != curr.location) {
            invalid_indices.insert(ev.idx);
            invalid_indices.insert(curr.idx);
          }
        }
      }
    }

    for (int idx : invalid_indices) result.push_back(transactions[idx]);
    return result;
  }
};
