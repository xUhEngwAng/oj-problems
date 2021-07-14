/*
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};*/
class Solution {
public:
    int length(ListNode* head){
        ListNode* curr = head;
        int ret = 0;
        while(curr){
            ret += 1;
            curr = curr->next;
        }
        return ret;
    }
    
    ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
        int len1 = length(pHead1);
        int len2 = length(pHead2);
        while(len1 > len2){
            pHead1 = pHead1->next;
            len1 -= 1;
        }
        while(len1 < len2){
            pHead2 = pHead2->next;
            len2 -= 1;
        }
        while(pHead1 != pHead2){
            pHead1 = pHead1->next;
            pHead2 = pHead2->next;
        }
        
        return pHead1;
    }
};
