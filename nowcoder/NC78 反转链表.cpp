/*
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x): val(x), next(NULL) {}
};*/

#include <stack>
using std::stack;

class Solution {
public:
    ListNode* ReverseList(ListNode* pHead) {
        // normal solution: adjust pointers between nodes

        ListNode *curr = pHead, *prev = nullptr, *next;

        while(curr){
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        return prev;

        // naive solution: use a stack
        /*
        stack<ListNode*> s;
        ListNode* temp = pHead;

        while(temp){
            s.push(temp);
            temp = temp->next;
        }

        ListNode *ret, *curr;
        if(s.empty()) return nullptr;

        curr = ret = s.top();
        s.pop();

        while(!s.empty()){
            temp = s.top();
            s.pop();
            curr->next = temp;
            curr = curr->next;
        }

        curr->next = nullptr;

        return ret;
        */
    }
};
