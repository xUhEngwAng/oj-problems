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
    ListNode *detectCycle(ListNode *head) {
        if(!head) return nullptr;
        ListNode *slow = head, *fast = head;

        while(true){
            slow = slow->next;
            fast = fast->next;
            if(!fast) break;
            fast = fast->next;
            if(!fast || slow == fast) break;
        }

        if(!fast) return nullptr;
        fast = head;
        
        while(slow != fast){
            slow = slow->next;
            fast = fast->next;
        }

        return slow;
    }
};
