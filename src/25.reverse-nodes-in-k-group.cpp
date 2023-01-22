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
  ListNode* reverseKGroup(ListNode* head, int k) {
    if (k == 1) return head;
    // make sliding window of size k
    // make sure the sliding window size == k
    // reverse linked list nodes in the sliding window

    ListNode dummy(0, head);
    auto prev_head = &dummy;

    while (true) {
      int count = 0;
      auto curr = prev_head->next;
      while (count < k && curr) {
        curr = curr->next;
        count++;
      }
      if (count != k) break;

      prev_head = reverse(prev_head, k);
    }

    return dummy.next;
  }

  ListNode* reverse(ListNode* prev_head, int k) {
    // x -> 1 -> 2 -> 3 -> xxx
    // x -> 1 <- 2 -> 3 -> xxx
    // x -> 1 <- 2 <- 3 -> xxx

    auto curr = prev_head->next;
    ListNode* prev = nullptr;
    for (int i = 0; i < k; ++i) {
      auto tmp = curr;
      curr = curr->next;
      tmp->next = prev;
      prev = tmp;
    }

    auto new_prev_head = prev_head->next;
    new_prev_head->next = curr;
    prev_head->next = prev;
    return new_prev_head;
  }
};
