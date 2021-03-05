/**
 * struct ListNode {
 *	int val;
 *	struct ListNode *next;
 * };
 */

class Solution {
public:
    /**
     * 
     * @param head ListNode类 
     * @param n int整型 
     * @return ListNode类
     */
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // write code here
        // A better solution: two pointers 
        ListNode *first, *second, *prev;
        first = second = head;
        
        while(n--){
            second = second->next;
        }
        
        prev = nullptr;
        
        while(second){
            second = second->next;
            prev = first;
            first = first->next;
        }
        
        if(prev) prev->next = first->next;
        else           head = head->next;
        
        return head;
        
        // my solution: two loops
        /*
        int length = 0;
        ListNode *tmp = head, *prev;
        
        while(tmp){
            length++;
            tmp = tmp->next;
        }
        
        length = length - n;
        tmp = head, prev = nullptr;
        
        while(length--){
            prev = tmp;
            tmp = tmp->next;
        }
        
        if(prev) prev->next = tmp->next;
        else           head = head->next;
        
        return head;
        */
    }
};