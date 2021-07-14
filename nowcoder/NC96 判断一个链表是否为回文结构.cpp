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
     * @param head ListNode类 the head
     * @return bool布尔型
     */
    ListNode* reverse(ListNode *head){
        ListNode *prev, *curr, *next;
        prev = nullptr;
        curr = head;
        while(curr){
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }
    
    bool isPail(ListNode* head) {
        // write code here
        ListNode *one, *two;
        one = two = head;
        while(two){
            one = one->next;
            two = two->next;
            if(!two) break;
            two = two->next;
        }
        two = reverse(one);
        one = head;
        while(one && two){
            if(one->val != two->val) return false;
            one = one->next;
            two = two->next;
        }
        return true;
    }
};
