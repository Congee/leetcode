#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  std::unordered_map<int, std::string> map = {
    {1, "One"},
    {2, "Two"},
    {3, "Three"},
    {4, "Four"},
    {5, "Five"},
    {6, "Six"},
    {7, "Seven"},
    {8, "Eight"},
    {9, "Nine"},
    {10, "Ten"},
    {11, "Eleven"},
    {12, "Twelve"},
    {13, "Thirteen"},
    {14, "Fourteen"},
    {15, "Fifteen"},
    {16, "Sixteen"},
    {17, "Seventeen"},
    {18, "Eighteen"},
    {19, "Nineteen"},
    {20, "Twenty"},
    {30, "Thirty"},
    {40, "Forty"},
    {50, "Fifty"},
    {60, "Sixty"},
    {70, "Seventy"},
    {80, "Eighty"},
    {90, "Ninety"},
    {100, "Hundred"},
    {1000, "Thousand"},
    {1000000, "Million"},
    {1000000000, "Billion"},
  };

 public:
  string numberToWords(int num) {
    if (num == 0) return "Zero";
    // int32 at most 10 digits
    auto digits = std::to_string(num);

    std::vector<std::string> vec;

    int count3 = 0;
    while (digits.size()) {
      auto pos = std::max((int)digits.size() - 3, 0);
      auto size = std::min(3, (int)digits.size());
      auto str = digits.substr(pos, size);
      if (str != "000"s) {
        auto v3 = do3(str);
        if (v3.size()) {
          if (count3 == 0)
            ;
          else if (count3 == 1)
            vec.push_back("Thousand");
          else if (count3 == 2)
            vec.push_back("Million");
          else if (count3 == 3)
            vec.push_back("Billion");
        }
        for (auto&& x : v3) vec.push_back(x);
      }

      auto to_pop = std::min(digits.size(), 3ul);
      for (size_t i = 0; i < to_pop; ++i) digits.pop_back();

      count3++;
    }

    std::string str;
    while (vec.size()) {
      str += vec.back();
      str += ' ';
      vec.pop_back();
    }

    str.pop_back();

    return str;
  }

  std::vector<std::string> do2(const std::string& digits) {
    auto num = std::stoi(digits);
    if (num < 21)
      return {map[std::stoi(digits)]};
    else if (num % 10)
      return {map[num % 10], map[num / 10 * 10]};
    else
      return {map[num / 10 * 10]};
  }

  std::vector<std::string> do3(const std::string& digits) {
    if (digits.size() < 3) {
      return do2(digits);
    } else {
      std::vector<std::string> vec;
      if (digits.substr(1, 2) != "00"s)
        for (auto&& x : do2(digits.substr(1, 2))) vec.push_back(x);

      if (digits.front() != '0') {
        vec.push_back("Hundred");
        vec.push_back(map[digits.front() - '0']);
      }
      return vec;
    }
  }
};
