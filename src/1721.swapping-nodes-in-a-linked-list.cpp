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
  ListNode* swapNodes(ListNode* head, int k) {
    return one_pass(head, k);
    return naive(head, k);
  }

  ListNode* one_pass(ListNode* head, int k) {
    ListNode *curr = head, *lo = nullptr, *hi = nullptr;
    // 1 2 3 4 5
    for (int count = 1; curr; count++, curr = curr->next) {
      if (count == k) lo = curr, hi = head;
      if (count > k) hi = hi->next;
    }
    std::swap(lo->val, hi->val);
    return head;
  }

  ListNode* naive(ListNode* head, int k) {
    std::vector<ListNode*> vec;
    for (auto curr = head; curr; curr = curr->next) vec.push_back(curr);
    std::swap(vec[k - 1]->val, vec[vec.size() - k]->val);
    return head;
  }
};
