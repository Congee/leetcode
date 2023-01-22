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
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    // reverse two lists
    // perform addition
    // reverse the result
    // return the result

    l1 = reverse(l1);
    l2 = reverse(l2);
    return reverse(add(l1, l2));
  }

  ListNode* reverse(ListNode* head) {
    ListNode *prev = nullptr, *curr = head;
    while (curr) {
      auto tmp = curr;
      curr = curr->next;
      tmp->next = prev;
      prev = tmp;
    }

    return prev;
  }

  ListNode* add(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    auto head = &dummy;
    int carry = 0;
    while (l1 || l2 || carry) {
      int sum = carry;
      if (l1) sum += l1->val;
      if (l2) sum += l2->val;
      carry = sum / 10;
      sum %= 10;
      head->next = new ListNode(sum, nullptr);
      head = head->next;
      if (l1) l1 = l1->next;
      if (l2) l2 = l2->next;
    }

    return dummy.next;
  }
};
