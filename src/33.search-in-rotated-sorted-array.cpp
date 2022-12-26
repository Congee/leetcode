#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  int search(vector<int>& nums, int target) {
    return onepass(nums, target);

    if (nums.size() < 2) {
      if (nums[0] == target) return 0;
      return -1;
    }

    if (nums.front() < nums.back()) {  // sorted
      return bs(nums, target, 0, nums.size() - 1);
    }

    int min_idx = find_min(nums, target);
    if (target >= nums.front())
      return bs(nums, target, 0, min_idx - 1);
    else
      return bs(nums, target, min_idx, nums.size() - 1);
  }

  int bs(vector<int>& nums, int target, int lo, int hi) {
    while (lo <= hi) {
      int mid = lo + (hi - lo) / 2;
      if (nums[mid] == target)
        return mid;
      else if (nums[mid] < target)
        lo = mid + 1;
      else
        hi = mid - 1;
    }
    return -1;
  }

  int onepass(vector<int>& nums, int target) {
    int lo = 0;
    int hi = nums.size() - 1;
    int left_min = nums.front();
    int right_max = nums.back();

    while (lo <= hi) {
      int mid = lo + (hi - lo) / 2;

      if (nums[mid] == target)
        return mid;

      else if (nums[mid] >= left_min) {
        if (nums[mid] > target && target >= left_min) {
          hi = mid - 1;
        } else
          lo = mid + 1;
        // } else if (nums[mid] < right_max) {
      } else {
        if (nums[mid] < target && target <= right_max)
          lo = mid + 1;
        else
          hi = mid - 1;
      }
    }
    return -1;
  }

  int find_min(vector<int>& nums, int target) {
    int lo = 0;
    int hi = nums.size() - 1;
    int left_min = nums.front();
    int right_max = nums.back();

    // [4,5,6,(7),0,1,2]
    // [7,(0),1,2]
    // [7,0]
    while (lo + 1 != hi) {
      int mid = lo + (hi - lo) / 2;

      if (nums[mid] > left_min)
        lo = mid;
      else if (nums[mid] < right_max)
        hi = mid;
    }
    return hi;
  }
};
