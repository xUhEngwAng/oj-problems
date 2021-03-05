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
     * @param l1 ListNode类 
     * @param l2 ListNode类 
     * @return ListNode类
     */
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        // write code here
        ListNode *head = new ListNode(-1), *curr = head;
        ListNode *p1 = l1, *p2 = l2;
        
        while(p1 || p2){
            if(!p2){
                curr->next = p1;
                p1 = p1->next;
            }
            else
            if(!p1){
                curr->next = p2;
                p2 = p2->next;
            }
            else
            if(p1->val < p2->val){
                curr->next = p1;
                p1 = p1->next;
            }
            else{
                curr->next = p2;
                p2 = p2->next;
            }
            curr = curr->next;
        }
        
        return head->next;
    }
};