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
    static bool cmp(const ListNode* one, const ListNode* two){
        return one->val > two->val;
    }
    
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        vector<ListNode*> heap;
        heap.reserve(lists.size());
        for(auto list : lists){
            if(list) heap.push_back(list);
        }
        make_heap(heap.begin(), heap.end(), cmp);
        ListNode *ret, *curr, *next;
        ret = new ListNode(-1);
        curr = ret;
        while(!heap.empty()){
            next = heap.front();
            pop_heap(heap.begin(), heap.end(), cmp);
            heap.pop_back();
            curr->next = next;
            curr = next;
            if(curr->next){
                heap.push_back(curr->next);
                push_heap(heap.begin(), heap.end(), cmp);
            }
        }
        return ret->next;
    }
};
