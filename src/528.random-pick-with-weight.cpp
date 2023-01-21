#ifdef __LOCAL__
#include <leetcode.h>
#endif

#include <random>

std::random_device rd;
std::mt19937 gen(rd());

class Solution {
  std::vector<int> psum;
  std::uniform_int_distribution<> distrib;

 public:
  Solution(vector<int>& w) {
    psum.resize(w.size());
    std::inclusive_scan(w.begin(), w.end(), psum.begin());
    distrib = std::uniform_int_distribution<>(1, psum.back());
  }

  int pickIndex() {
    int key = distrib(gen);
    return std::lower_bound(psum.begin(), psum.end(), key) - psum.begin();
  }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */
