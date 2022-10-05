#include <vector>
using std::vector;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    static bool compare(ListNode* lh, ListNode* rh){
        if(!lh) return false;
        if(!rh) return true;
        return rh->val < lh->val;
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* header = new ListNode(), *curr = header, *minnode;
        make_heap(lists.begin(), lists.end(), compare);
        while(!lists.empty() && !lists.front()) {
            pop_heap(lists.begin(), lists.end(), compare);
            lists.pop_back();
        }

        while(!lists.empty()){
            pop_heap(lists.begin(), lists.end(), compare);
            minnode = lists.back();
            lists.pop_back();
            if(minnode->next){
                lists.push_back(minnode->next);
                push_heap(lists.begin(), lists.end(), compare);
            }
            curr->next = new ListNode(minnode->val);
            curr = curr->next;
        }

        return header->next;
    }
};
