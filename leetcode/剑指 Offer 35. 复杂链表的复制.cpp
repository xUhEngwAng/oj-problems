#include <unordered_map>
using std::unordered_map;

class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

/*
 * 这个题还挺有意思的，本来我的解法是要使用一个哈希表来保存
 * 原来的节点到对应的新节点的映射，所以时空复杂度都是 O(n)。
 * 看题解有一种将空间复杂度降低到 O(1) 的解法。
 *
 * 具体的做法也非常巧妙，即给每个节点创建一个镜像的新节点，
 * 跟在这个节点后面，这些新的节点即是最终要返回的节点。为此
 * 需要进行三次遍历，第一次遍历构造所有新的节点，第二次遍历
 * 更新新节点的 random 指针，第三次遍历将新老节点拆分成两个
 * 链表，实现起来还是挺多细节的。
 */

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(!head) return nullptr;
        Node *curr = head, *mirror, *ret;

        while(curr){
            mirror = new Node(curr->val);
            mirror->next = curr->next;
            curr->next = mirror;
            curr = mirror->next;
        }

        curr = head;

        while(curr){
            mirror = curr->next;
            if(!curr->random) mirror->random = nullptr;
            else mirror->random = curr->random->next;
            curr = mirror->next;
        }

        curr = head;
        ret = head->next;

        while(curr){
            mirror = curr->next;
            curr->next = mirror->next;
            curr = curr->next;
            if(curr) mirror->next = curr->next;
        }

        return ret;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(!head) return nullptr;
        unordered_map<Node*, Node*> ptr2node;
        Node *ret = new Node(head->val), *curr_new = ret, *curr_old = head;
        ptr2node[head] = ret;

        while(curr_new){
            if(!curr_old->next) curr_new->next = nullptr;
            else{
                if(!ptr2node.count(curr_old->next))
                    ptr2node[curr_old->next] = new Node(curr_old->next->val);
                curr_new->next = ptr2node[curr_old->next];
            }

            if(!curr_old->random) curr_new->random = nullptr;
            else{
                if(!ptr2node.count(curr_old->random))
                    ptr2node[curr_old->random] = new Node(curr_old->random->val);
                curr_new->random = ptr2node[curr_old->random];
            }

            curr_new = curr_new->next;
            curr_old = curr_old->next;
        }

        return ret;
    }
};
