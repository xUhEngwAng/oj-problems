/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* deleteNode(ListNode* head, int val) {
        ListNode *sentinel = new ListNode(-1);
        ListNode *prev = sentinel, *curr = head;
        sentinel->next = head;

        while(curr && curr->val != val){
            curr = curr->next;
            prev = prev->next;
        }

        prev->next = curr->next;
        return sentinel->next;
    }
};
