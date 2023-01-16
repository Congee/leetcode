#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  vector<double> medianSlidingWindow(vector<int>& nums, int k) {
    return two_heaps_lazy_deletion(nums, k);
    return one_multiset_one_pointer(nums, k);
  }

  vector<double> two_heaps_lazy_deletion(vector<int>& nums, int k) {
    // the key is to count only number of valid elements rather than the heap
    // size
    std::unordered_map<int, int> to_delete;
    std::unordered_map<int, int>::iterator it;
    std::priority_queue<int> lo;
    std::priority_queue<int, std::vector<int>, std::greater<int>> hi;
    std::vector<double> medians;

    int i = 0;
    while (i < k) lo.push(nums[i++]);
    for (int j = 0; j < k / 2; ++j) {
      hi.push(lo.top());
      lo.pop();
    }

    while (true) {
      medians.push_back(k & 1 ? lo.top() : ((double)lo.top() + hi.top()) * 0.5);

      if (i == (int)nums.size()) break;

      int out = nums[i - k], in = nums[i++];
      // balance == 0: balanced
      // balance <  0: lo needs more; move one from hi to lo
      // balance >  0: hi needs more; move one from lo to hi
      int balance = out <= lo.top() ? -1 : 1;
      to_delete[out]++;

      // insertion
      if (in <= lo.top()) {
        lo.push(in);
        balance++;
      } else {
        hi.push(in);
        balance--;
      }

      // rebalance
      if (balance < 0) {
        lo.push(hi.top());
        hi.pop();
        balance++;
      }

      if (balance > 0) {
        hi.push(lo.top());
        lo.pop();
        balance--;
      }

      // lazy deletion
      while ((it = to_delete.find(lo.top())) != to_delete.end()) {
        if (--it->second == 0) to_delete.erase(it);
        lo.pop();
      }

      while (hi.size() && (it = to_delete.find(hi.top())) != to_delete.end()) {
        if (--it->second == 0) to_delete.erase(it);
        hi.pop();
      }
    }

    return medians;
  }

  vector<double> one_multiset_one_pointer(vector<int>& nums, int k) {
    std::vector<double> medians;
    std::multiset<int> window(nums.begin(), nums.begin() + k);
    auto mid = std::next(window.begin(), k / 2);

    for (size_t i = k;; i++) {
      medians.push_back(((double)(*mid) + *std::next(mid, k % 2 - 1)) * 0.5);

      if (i == nums.size()) break;

      window.insert(nums[i]);
      if (nums[i] < *mid) mid--;
      if (nums[i - k] <= *mid) mid++;

      window.erase(window.find(nums[i - k]));
    }

    return medians;
  }

  vector<double> two_multisets(vector<int>& nums, int k) {
    if (k == 1) return std::vector<double>(nums.begin(), nums.end());

    std::multiset<int> lo, hi;

    std::vector<double> vec;
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
      // remove stale
      if (i >= k) {
        if (nums[i - k] <= *lo.rbegin()) {
          lo.erase(lo.find(nums[i - k]));
        } else {
          hi.erase(hi.find(nums[i - k]));
        }
      }

      // insert new
      if (lo.size() <= hi.size()) {
        lo.insert(nums[i]);
      } else {
        hi.insert(nums[i]);
      }

      // rebalance
      if (lo.size() && hi.size() && *lo.rbegin() > *hi.begin()) {
        auto l = *lo.rbegin();
        auto r = *hi.begin();
        lo.erase(std::prev(lo.end()));
        hi.erase(hi.begin());
        lo.insert(r);
        hi.insert(l);
      }

      if (lo.size() + hi.size() < (size_t)k) continue;

      // calculate median
      if (lo.size() > hi.size()) {
        vec.push_back(*lo.rbegin());
      } else if (lo.size() < hi.size()) {
        vec.push_back(*hi.begin());
      } else {
        vec.push_back((*lo.rbegin() + *hi.begin()) / 2.0);
      }
    }

    return vec;
  }
};
