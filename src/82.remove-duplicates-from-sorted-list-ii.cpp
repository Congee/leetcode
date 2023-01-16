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
  ListNode* deleteDuplicates(ListNode* head) {
    ListNode dummy(INT_MIN, head);
    auto node = &dummy;

    while (node->next) {
      if (node->next && node->next->next && node->next->val == node->next->next->val) {
        int dup_val = node->next->val;
        // n -> 2 -> 2 -> null
        //      x
        while (node->next && node->next->val == dup_val) {
          auto mid = node->next;
          node->next = node->next->next;
          delete mid;
        }
      } else {
        node = node->next;
      }
    }

    return dummy.next;
  }
};
