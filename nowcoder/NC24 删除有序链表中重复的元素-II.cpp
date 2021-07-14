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
     * @return ListNode类
     */
    ListNode* deleteDuplicates(ListNode* head) {
        // write code here
        ListNode* ret = new ListNode(-32768);
        ListNode *curr, *next, *prev = ret;
        curr = ret->next = head;
        int cnt;
        
        while(curr){
            cnt = 1;
            while(true){
                if(curr->next && curr->val == curr->next->val){
                    curr = curr->next;
                    cnt += 1;
                }
                else break;
            }
            if(cnt == 1){
                prev->next = curr;
                prev = curr; 
            }
            curr = curr->next;
        }
        prev->next = nullptr;
        
        return ret->next;
    }
};
