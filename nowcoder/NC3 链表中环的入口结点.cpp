/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};
*/
class Solution {
public:
    ListNode* EntryNodeOfLoop(ListNode* pHead) {
        ListNode *slow, *fast;
        slow = fast = pHead;
        while(true){
            if(!fast) return nullptr;
            slow = slow->next;
            fast = fast->next;
            if(!fast) return nullptr;
            fast = fast->next;
            if(slow == fast) break;
        }
        slow = pHead;
        while(slow != fast){
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }
};
