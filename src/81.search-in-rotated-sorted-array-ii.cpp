#ifdef __LOCAL__
#include <leetcode.h>
#endif

class Solution {
 public:
  bool search(vector<int>& nums, int target) {
    return bs(nums, target);
    return naive(nums, target);
  }

  bool bs(vector<int>& nums, int target) {
    int lo = 0, hi = nums.size() - 1;

    while (lo <= hi) {
      while (lo < hi && nums[lo] == nums[lo + 1]) lo++;
      while (lo < hi && nums[hi] == nums[hi - 1]) hi--;

      int mid = lo + (hi - lo) / 2;
      if (nums[mid] == target) return true;

      if (nums[mid] >= nums[lo]) {
        if (nums[mid] < target || (target < nums[lo] && target < nums[mid]))
          lo = mid + 1;
        else
          hi = mid - 1;
      } else {
        if (nums[mid] < target && target < nums[lo])
          lo = mid + 1;
        else
          hi = mid - 1;
      }
    }

    return false;
  }

  bool naive(vector<int>& nums, int target) {
    int lo = 0, hi = nums.size() - 1, n = nums.size();

    if (n == 1) return nums[0] == target;
    if (nums.front() == target || nums.back() == target) return true;

    //        /
    //       /
    //     --
    //___ /      _____
    //         /

    while (lo + 1 < n && nums[lo] == nums[lo + 1]) lo++;
    while (hi - 1 >= 0 && nums[hi - 1] == nums[hi]) hi--;
    int pivot = nums[lo];

    while (lo <= hi) {
      int mid = lo + (hi - lo) / 2;

      // 1, 3,3,3,3,3, 4  <- 2
      if (nums[lo] == nums[mid] && nums[mid] == nums[hi])
        return target == nums[lo];

      // [4,5,6,7,0,1,2]
      if (nums[mid] == target) return true;

      if (0)
        ;
      else if (pivot <= nums[mid] && nums[mid] < target)
        lo = mid + 1;
      else if (pivot < target && target < nums[mid])
        hi = mid - 1;

      else if (nums[mid] <= pivot && pivot < target)
        hi = mid - 1;
      else if (target < pivot && pivot <= nums[mid])
        lo = mid + 1;

      else if (pivot > target && target < nums[mid])
        hi = mid - 1;
      else if (pivot > target && target > nums[mid])
        lo = mid + 1;
    }

    return false;
  }
};
