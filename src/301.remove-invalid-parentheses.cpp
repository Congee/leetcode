#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  std::string path;
  std::unordered_set<std::string> result{""};
  size_t max_len = 0, open = 0;

 public:
  vector<string> removeInvalidParentheses(string& s) {
    // for each parenthesis, do nothing or remove
    // the constarints said at most 20 parentheses
    // 2 ^ 20 == 1024 * 1024 = 1e6
    // So, just dfs
    // we can prune on validity
    // the length is 25 at most, we can use a bitmask

    return bfs(s);

    smart_dfs(s, 0, 0, '(', ')');
    return std::vector<std::string>(result.begin(), result.end());

    dfs(s, 0);
    return std::vector<std::string>(result.begin(), result.end());
  }

  void smart_dfs(std::string s, int istart, int jstart, char open, char close) {
    int num_open = 0, num_close = 0;
    for (int i = istart; i < (int)s.size(); ++i) {
      if (s[i] == open) num_open++;
      if (s[i] == close) num_close++;
      if (num_close > num_open) {  // remove the first ) to make a valid string
        for (int j = jstart; j <= i; ++j)
          if (s[j] == close && (j == jstart || s[j - 1] != close))
            // "())"
            // removing the 1st or 2nd ) results in the same output ()
            // keep track of the last removal of ) and only remove ) after that
            smart_dfs(s.substr(0, j) + s.substr(j + 1), i, j, open, close);
        return;
      }
    }

    // no invalid string
    // '(()(()'
    auto copy = s;
    std::reverse(copy.begin(), copy.end());
    if (open == '(')
      smart_dfs(copy, 0, 0, ')', '(');
    else
      result.insert(copy);
  }

  std::vector<std::string> bfs(string& s) {
    auto is_valid = [](const std::string& str) {
      int open = 0;
      for (char ch : str) {
        switch (ch) {
          case '(': open++; break;
          case ')':
            if (--open < 0) return false;
        }
      }
      return open == 0;
    };
    if (is_valid(s)) return {s};

    std::vector<std::string> result;
    std::unordered_set<std::string> seen;
    std::queue<std::string> queue({s});
    while (queue.size()) {
      const int size = queue.size();
      for (int i = 0; i < size; ++i) {
        auto& curr = queue.front();

        for (size_t j = 0; j < curr.size(); ++j) {
          if (std::isalpha(curr[j])) continue;

          auto str = curr.substr(0, j) + curr.substr(j + 1);
          if (!seen.emplace(str).second) continue;
          queue.push(str);

          if (is_valid(str)) result.push_back(str);
        }

        queue.pop();
      }
      if (result.size()) return result;
    }

    return {""};
  }

  bool dfs(string& s, size_t idx) {
    if (idx == s.size()) {
      if (open == 0) {  // valid
        if (max_len < path.size()) {
          max_len = path.size();
          result.clear();
          result.insert(path);
        } else if (max_len == path.size()) {
          result.insert(path);
        }
      }

      return open == 0;
    }

    if (std::isalpha(s[idx])) {
      path.push_back(s[idx]);
      bool ok = dfs(s, idx + 1);
      path.pop_back();
      return ok;
    }

    if (s[idx] == '(') {
      // add
      path.push_back(s[idx]);
      open++;
      bool ok = dfs(s, idx + 1);
      path.pop_back();
      open--;

      // skip
      ok |= dfs(s, idx + 1);

      return ok;
    }

    if (s[idx] == ')') {
      if (open == 0) return dfs(s, idx + 1);

      // add
      path.push_back(s[idx]);
      open--;
      bool ok = dfs(s, idx + 1);
      path.pop_back();
      open++;

      // skip
      ok |= dfs(s, idx + 1);
      return ok;
    }

    __builtin_unreachable();
  }
};
