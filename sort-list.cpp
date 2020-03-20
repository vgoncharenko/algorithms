//
// Created by Vitaliy on 2019-09-26.
// https://leetcode.com/problems/sort-list
//
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class MergeSortList {
public:
    ListNode* sortList(ListNode* head) {
      if (head == nullptr || head->next == nullptr)
        return head;
      ListNode *cur = head,
              *slow = head,
              *fast = head,
              *leftSide,
              *rightSide;
      while(fast != nullptr && fast->next != nullptr) {
        cur = slow;
        slow = slow->next;
        fast = fast->next->next;
      }
      cur->next = nullptr;

      leftSide = sortList(head);
      rightSide = sortList(slow);

      return merge(leftSide, rightSide);
    }

    ListNode* merge(ListNode* l, ListNode* r) {
      ListNode *result = new ListNode(0),
              *cur = result;

      while(l || r) {
        if (!l) {
          cur->next = r;
          r = r->next;
        } else if (!r) {
          cur->next = l;
          l = l->next;
        } else if (l->val <= r->val) {
          cur->next = l;
          l = l->next;
        } else if (l->val > r->val) {
          cur->next = r;
          r = r->next;
        }
        cur = cur->next;
      }

      return result->next;
    }
};