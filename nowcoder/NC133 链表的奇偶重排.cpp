/**
 * struct ListNode {
 *	int val;
 *	struct ListNode *next;
 *	ListNode(int x) : val(x), next(nullptr) {}
 * };
 */
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param head ListNode类 
     * @return ListNode类
     */
    ListNode* oddEvenList(ListNode* head) {
        // write code here
        if(!head) return nullptr;
        ListNode* odd_head = head, *even_head = head->next;
        
        ListNode *prev, *curr = odd_head, *next = curr->next;
        bool is_odd = true;
        while(next){
            curr->next = next->next;
            prev = curr;
            curr = next;
            next = next->next;
            is_odd = is_odd ^ 1;
        }
        if(is_odd) curr->next = even_head;
        else prev->next = even_head;
        return odd_head;
    }
};
