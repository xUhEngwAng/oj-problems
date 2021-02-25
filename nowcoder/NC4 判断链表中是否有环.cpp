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
    bool hasCycle(ListNode *head) {
        // two pointer solution
        
        ListNode *fast, *slow;
        fast = slow = head;
        
        while(fast && fast->next){
            fast = fast->next->next;
            slow = slow->next;
            if(fast == slow) return true;
        }
        
        return false;
        
        // naive solution, O(n^2) time complexity and O(1) space complexity
        /*
        ListNode *cur = head, *tmp;
        int cnt = 0, ix;
        
        while(cur){
            cur = cur->next;
            cnt = cnt + 1;
           
            for(tmp = head, ix = 0; ix != cnt; ++ix){
                if(tmp == cur) return true;
                tmp = tmp ->next;
            }
        }
        
        return false;
        */
    }
};