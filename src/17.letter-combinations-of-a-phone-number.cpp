#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  vector<string> letterCombinations(string digits) {
    if (digits.empty()) return {};

    std::vector<string> pool;

    for (auto d : digits) {
      switch (d) {
        case '2': pool.push_back("abc"); break;
        case '3': pool.push_back("def"); break;
        case '4': pool.push_back("ghi"); break;
        case '5': pool.push_back("jkl"); break;
        case '6': pool.push_back("mno"); break;
        case '7': pool.push_back("pqrs"); break;
        case '8': pool.push_back("tuv"); break;
        case '9': pool.push_back("wxyz"); break;
        default: break;
      }
    }

    std::string str;
    std::vector<string> result;

    bt(pool, str, 0, 0, result);

    return result;
  }

  void bt(
    std::vector<string>& pool,
    string& str,
    int key_idx,
    int letter_idx,
    std::vector<std::string>& result
  ) {
    if (str.size() == pool.size()) {
      result.push_back(str);
      return;
    }

    for (int i = letter_idx; i < pool[key_idx].size(); ++i) {
      str += pool[key_idx][i];
      bt(pool, str, key_idx + 1, letter_idx, result);
      str.pop_back();
    }
  }
};
