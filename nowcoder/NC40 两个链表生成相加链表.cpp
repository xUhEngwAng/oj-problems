/**
 * struct ListNode {
 *	int val;
 *	struct ListNode *next;
 * };
 */

class Solution {
public:
    ListNode* reverse(ListNode* head){
        ListNode *prev = nullptr, *curr = head, *next;

        while(curr){
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        return prev;
    }
    /**
     * 
     * @param head1 ListNode类 
     * @param head2 ListNode类 
     * @return ListNode类
     */
    ListNode* addInList(ListNode* head1, ListNode* head2) {
        // write code here
        head1 = reverse(head1);
        head2 = reverse(head2);
        //printList(head1);
        
        int one, two, carry = 0, res;
        ListNode *ret = new ListNode(-1), *tmp = ret;
        
        while(head1 || head2){
            one = (head1? head1->val: 0);
            two = (head2? head2->val: 0);
            res = one + two + carry;
            if(res >= 10){
                res -= 10;
                carry = 1;
            }else{
                carry = 0;
            }
            tmp->next = new ListNode(res);
            tmp = tmp->next;
            if(head1) head1 = head1->next;
            if(head2) head2 = head2->next;
        }
        
        if(carry) tmp->next = new ListNode(1);
        
        return reverse(ret->next);
    }
};
