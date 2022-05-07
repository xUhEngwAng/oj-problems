#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode *prev = nullptr, *curr = head;
        int length = right - left + 1;

        while(--left){
            prev = curr;
            curr = curr->next;
        }

        curr = reverse(curr, length);
        if(!prev) return curr;
        prev->next = curr;
        return head;
    }

    ListNode* reverse(ListNode* head, int length){
        ListNode *prev = nullptr, *curr = head, *next;

        while(length--){
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        head->next = curr;
        return prev;
    }
};
