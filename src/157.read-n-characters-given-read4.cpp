#ifdef __LOCAL__
#include <leetcode.h>
#endif

/**
 * The read4 API is defined in the parent class Reader4.
 *     int read4(char *buf4);
 */

int read4(char *buf4);

class Solution {
 public:
  /**
   * @param buf Destination buffer
   * @param n   Number of characters to read
   * @return    The number of actual characters read
   */
  int read(char *buf, int n) {
    int count = 0;
    int r = 0;
    // buf overflows
    while (count < n && (r = read4(buf + count))) {
      count += r;
    }
    return std::min(count, n);
  }
};
