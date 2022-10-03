#ifdef __LOCAL__
#include <leetcode.h>
#endif

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
 public:
  ListNode* reverseBetween(ListNode* head, int left, int right) {
    if (left == right) return head;

    // left & right are 1-based indices
    auto dummy = ListNode(0, head);

    auto lprev = &dummy;
    auto rprev = &dummy;
    auto curr = &dummy;
    int lcount = 0;
    int rcount = 0;
    // 0 -> 1 -> 2
    while (curr) {
      if (lcount < left) {
        lcount++;
        lprev = curr;
      }
      if (rcount < right + 1) {
        rcount++;
        rprev = curr;
      }
      if (lcount == left && rcount == right + 1) break;

      curr = curr->next;
    }

    // 0 -> 1 -> 2 -> null
    // 0 -> 1 -> 2 -> 3 -> 4 -> 5 -> null
    int count = right - left;
    while (count--) {
      auto lnode = lprev->next;
      lprev->next = lnode->next;

      lnode->next = rprev->next;
      rprev->next = lnode;
    }

    return dummy.next;
  }
};
