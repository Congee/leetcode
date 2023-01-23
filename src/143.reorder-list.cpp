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
  void reorderList(ListNode* head) {
    // count n
    // queue up the right half
    // move head and consume the queue
    //
    // another approach is reversing the right half
    int n = count(head);
    if (n < 3) return;

    std::stack<ListNode*> stack;
    // 1 2 3 4 5
    // 1 2 3 4
    auto curr = head;
    for (int i = 0; i < n / 2 + (n & 1); ++i) curr = curr->next;
    while (curr) {
      stack.push(curr);
      curr = curr->next;
    }

    curr = head;
    while (stack.size()) {
      auto right = stack.top();
      stack.pop();

      right->next = curr->next;
      curr->next = right;
      curr = right->next;
    }

    curr->next = nullptr;
  }

  inline int count(ListNode* head) {
    auto curr = head;
    int total = 0;
    while (curr) {
      total++;
      curr = curr->next;
    }
    return total;
  }
};
