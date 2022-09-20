#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int strStr(const string_view& haystack, const string_view& needle) {
    return rabin_karp(haystack, needle);
  }

  // worst case
  // "aaabaaac"
  // "aaac"
  //
  // "aaaaaaac"
  // "aaac"
  int naive(const string& haystack, const string& needle) {
    for (size_t i = 0; i <= haystack.size() - needle.size(); ++i) {
      size_t j;
      for (j = 0; j < needle.size() && haystack[i + j] == needle[j]; ++j)
        ;
      if (j == needle.size()) return i;
    }
    return -1;
  }

  long hash(const string_view& str) {
    int p = 31;
    int m = 1e9 + 7;
    long p_pow = 1;
    long hashed = 0;
    for (size_t i = 0; i < str.size(); ++i) {
      hashed = (hashed + (str[i] - 'a' + 1) * p_pow) % m;
      p_pow = (p_pow * p) % m;
    }
    return hashed;
  }

  int rabin_karp_naive(const string_view& haystack, const string_view& needle) {
    if (haystack.size() < needle.size()) return -1;

    long roll = hash(haystack.substr(0, needle.size()));
    long target = hash(needle);
    if (roll == target && needle == haystack.substr(0, needle.size())) return 0;

    int p = 31;
    int m = 1e9 + 7;
    long pow_hi = 1;
    long pow_lo = 1;
    for (size_t i = 1; i <= needle.size(); ++i) pow_hi = (pow_hi * p) % m;

    // "a aa b"
    // "ab"
    for (size_t i = needle.size(); i < haystack.size(); ++i) {
      roll = (roll + m - (haystack[i - needle.size()] - 'a' + 1) * pow_lo % m) % m;
      roll = (roll + (haystack[i] - 'a' + 1) * pow_hi % m) % m;
      target = (target * p) % m;
      pow_hi = (pow_hi * p) % m;
      pow_lo = (pow_lo * p) % m;

      if (roll == target)
        if (needle == haystack.substr(i - needle.size() + 1, needle.size()))
          return i - needle.size() + 1;
    }

    return -1;
  }

  long horner(const std::string_view& str) {
    // for lowercase alphabet
    int p = 31;
    int m = 1e9 + 7;
    long hashed = 0;
    for (char ch : str)
      hashed = (hashed * p + ch) % m;
    return hashed;
  }

  int rabin_karp(const string_view& haystack, const string_view& needle) {
    if (haystack.size() < needle.size()) return -1;

    long roll = horner(haystack.substr(0, needle.size()));
    long target = horner(needle);
    if (roll == target && needle == haystack.substr(0, needle.size())) return 0;

    int p = 31;
    int m = 1e9 + 7;
    long pow = 1; // p^(needle.size() - 1) % m
    for (int i = 1; i < m; ++i)
      pow = pow * p % m;

    for (size_t i = needle.size(); i < haystack.size(); ++i) {
      roll = (roll + m - pow * haystack[i - needle.size()] % m) % m;
      roll = (roll * p + haystack[i]) % m;
      if (roll == target)
        if (needle == haystack.substr(i - needle.size() + 1, needle.size()))
          return i - needle.size() + 1;
    }

    return -1;
  }
};
