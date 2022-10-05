#ifdef __LOCAL__
#include <leetcode.h>
#endif

class LUPrefix {
  std::vector<bool> vec;
  int ptr;

 public:
  LUPrefix(int n) : ptr(0) {
    vec.assign(n + 2, 0);
    vec[0] = 0;
  }

  void upload(int video) {
    vec[video] = 1;
    while (vec[ptr + 1]) ptr++;
  }

  int longest() { return ptr; }
};

/**
 * Your LUPrefix object will be instantiated and called as such:
 * LUPrefix* obj = new LUPrefix(n);
 * obj->upload(video);
 * int param_2 = obj->longest();
 */
