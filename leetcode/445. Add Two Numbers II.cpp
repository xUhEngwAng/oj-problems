#include <iostream>
#include <cstdio>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(): val(0), next(nullptr) {}
    ListNode(int x): val(x), next(nullptr) {}
    ListNode(int x, ListNode *next): val(x), next(next) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2){
        l1 = reverse(l1);
        l2 = reverse(l2);
        ListNode* ret = addReversedList(l1, l2);
        return reverse(ret);
    }

    ListNode* addReversedList(ListNode* l1, ListNode* l2){
        int carry = 0, lhv, rhv, res;
        ListNode *ret = new ListNode(), *curr = ret;
        
        while(l1 || l2){
            lhv = l1?l1->val: 0;
            rhv = l2?l2->val: 0;
            res = lhv + rhv + carry;
            carry = res / 10;
            res = res - 10 * carry;
            curr->next = new ListNode(res);
            curr = curr->next;

            if(l1) l1 = l1->next;
            if(l2) l2 = l2->next;
        }

        if(carry){
            curr->next = new ListNode(carry);
        }

        return ret->next;
    }

    void display(ListNode* l){
        ListNode *curr = l;
        if(curr){
            std::cout << curr->val;
            curr = curr->next;
        }

        while(curr){
            std::cout << "-->" << curr->val;
            curr = curr->next;
        }

        std::cout << std::endl;
    }

    ListNode* reverse(ListNode* l){
        ListNode *prev = nullptr, *curr = l, *next;

        while(curr){
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        return prev;
    }
};

int main(){
    Solution solution;
    ListNode *l1 = new ListNode(), *l2 = new ListNode(), *p;
    int m, n, val;
    scanf("%d %d", &m, &n);

    p = l1;
    for(int ix = 0; ix != m; ++ix){
        scanf("%d", &val);
        p->next = new ListNode(val);
        p = p->next;
    }

    p = l2;
    for(int ix = 0; ix != n; ++ix){
        scanf("%d", &val);
        p->next = new ListNode(val);
        p = p->next;
    }

    l1 = l1->next;
    l2 = l2->next;
    solution.display(l1);
    solution.display(l2);
    ListNode* res = solution.addTwoNumbers(l1, l2);
    solution.display(res);
    return 0;
}

