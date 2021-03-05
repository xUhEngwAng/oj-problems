/**
 * struct ListNode {
 *	int val;
 *	struct ListNode *next;
 * };
 */

class Solution {
public:
    ListNode* reverseK(ListNode* head, int k, ListNode*& nhead, ListNode*& ntail){
        int cnt = 0;
        ListNode *curr = head, *prev = nullptr, *next, *ret;
        
        while(curr && cnt < k){
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
            ++cnt;
        }
        
        nhead = prev;
        ntail = head;
        ret = next;
        
        if(cnt < k){
            curr = nhead;
            prev = nullptr;
            
            while(cnt--){
                next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
            }
            
            ntail = nhead;
            nhead = head;
        }
        
        return ret;
    }
    
    /**
     * 
     * @param head ListNode类 
     * @param k int整型 
     * @return ListNode类
     */
    ListNode* reverseKGroup(ListNode* head, int k) {
        // write code here
        if(!head) return nullptr;
        ListNode *ret, *nhead, *ntail, *curr, *prevtail;
        curr = reverseK(head, k, ret, prevtail);
        
        while(curr){
            curr = reverseK(curr, k, nhead, ntail);
            prevtail->next = nhead;
            prevtail = ntail;
        }
        
        return ret;
    }
};