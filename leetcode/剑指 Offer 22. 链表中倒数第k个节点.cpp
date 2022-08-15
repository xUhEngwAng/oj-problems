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
    ListNode* getKthFromEnd(ListNode* head, int k) {
        int length = 0;
        ListNode* curr = head;
        while(curr){
            curr = curr->next;
            length += 1;
        }
        curr = head;
        k = length - k;
        while(k--){
            curr = curr->next;
        }
        return curr;
    }
};
