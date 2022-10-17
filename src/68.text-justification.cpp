#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
  vector<string> words;

 public:
  vector<string> fullJustify(vector<string>& __words, size_t maxWidth) {
    words = std::move(__words);
    int n = words.size();
    // case we cannot evenly distribute words
    // x__xx_x
    //
    // case words[i] == maxWidth
    //
    std::vector<std::string> vec;

    int lo = 0, hi = 0, len = 0;
    for (; hi < n; ++hi) {
      if (len + words[hi].size() + (hi - lo) == maxWidth) {
        vec.push_back(make(lo, hi, maxWidth));
        if (hi == n - 1) return vec;
        lo = hi + 1;
        len = 0;
      } else if (len + words[hi].size() + (hi - lo) > maxWidth) {
        if (lo != hi) vec.push_back(make(lo, hi - 1, maxWidth));
        lo = hi;
        len = words[hi].size();
      } else {
        len += words[hi].size();
      }
    }

    // trailing space
    vec.push_back("");
    for (int i = lo; i < hi; ++i) vec.back() += words[i] + " ";
    if (vec.back().size() > maxWidth) vec.back().pop_back();
    while (vec.back().size() < maxWidth) vec.back() += ' ';

    return vec;
  }

  // [
  //   "Science  is  what we",
  //   "understand      well",
  //   "enough to explain to",
  //   "a  computer.  Art is",
  //   "everything  else  we",
  //   "do                  "
  // ]
  std::string make(int lo, int hi, size_t maxWidth) {  // inclusive
    int count = hi - lo + 1;
    int len = 0;
    for (int i = lo; i <= hi; ++i) len += words[i].size();
    std::string each((maxWidth - len) / std::max(1, count - 1), ' ');

    std::string str;
    int extra = (maxWidth - len) % std::max(1, count - 1);

    for (int i = lo; i <= hi; ++i) {
      str.append(words[i]);
      str.append(each);
      if (extra-- > 0) str.push_back(' ');
    }

    while (str.size() > maxWidth) str.pop_back();
    while (str.size() < maxWidth) str += ' ';

    return str;
  }
};
