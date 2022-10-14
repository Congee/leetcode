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
  ListNode* deleteMiddle(ListNode* head) { return floyd(head); }

  ListNode* floyd(ListNode* head) {
    if (head->next == nullptr) return nullptr;

    auto fast = head, slow = head;
    auto prev = slow;

    while (fast && fast->next) {
      prev = slow;
      fast = fast->next->next;
      slow = slow->next;
    }

    auto mid = prev->next;
    prev->next = prev->next->next;
    delete mid;

    return head;
  }

  ListNode* naive(ListNode* head) {
    // delete n / 2
    ListNode dummy(0, head);
    auto fast = &dummy, slow = &dummy;

    // x -> 0 -> null
    // x -> 0 -> 1 -> null
    // x -> 0 -> 1 -> 2 -> null
    // x -> 0 -> 1 -> 2 -> 3 -> null
    while (fast->next && fast->next->next) {
      fast = fast->next->next;
      slow = slow->next;
    }

    // delete
    auto mid = slow->next;
    slow->next = mid->next;
    delete mid;

    return dummy.next;
  }
};
