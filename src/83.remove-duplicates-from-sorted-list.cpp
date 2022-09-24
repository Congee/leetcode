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
    auto curr = head;
    // 1-1-1-n
    // 1-1-1-1-n
    while (curr) {
      if (curr->next && curr->val == curr->next->val) {
        auto tmp = curr->next->next;
        delete curr->next;
        curr->next = tmp;
        continue;
      }
      curr = curr->next;
    }
    return head;
  }
};
