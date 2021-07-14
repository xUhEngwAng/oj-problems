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
    ListNode* reverse(ListNode* head){
        ListNode* curr = head, *prev = nullptr, *next;
        while(curr){
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }
    
    void reorderList(ListNode *head) {
        if(!head) return;
        int length = 0;
        ListNode *tmp = head, *tail, *next, *prev;
        while(tmp){
            length += 1;
            tmp = tmp->next;
        }
        tmp = head;
        length = (length + 1) >> 1;
        for(int ix = 0; ix != length; ++ix){
            prev = tmp;
            tmp = tmp->next;
        }
        prev->next = nullptr;
        tail = reverse(tmp);
        tmp = head;
        while(tail){
            next = tail->next;
            tail->next = tmp->next;
            tmp->next = tail;
            tmp = tail->next;
            tail = next;
        }
    }
};
