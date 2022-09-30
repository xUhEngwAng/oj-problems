#include <stack>
using std::stack;

/* 写了个中序非递归，感觉 next 写法挺好的，实现时思路
 * 比较清晰，以后就这样写了。此外，题目要求尽量就地算
 * 法，我理解这应该是做不到的，官方的题解也还用了递归
 * 呢。
 */

class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};

class Solution {
public:
    stack<Node*> s;

    Node* nextNode(Node* curr){
        Node* ret = curr->right;
        while(ret){
            s.push(ret);
            ret = ret->left;
        }
        if(s.empty()) return nullptr;
        ret = s.top();
        s.pop();
        return ret;
    }

    Node* treeToDoublyList(Node* root) {
        if(!root) return nullptr;
        
        Node *curr = root, *next, *ret;
        
        while(curr){
            s.push(curr);
            curr = curr->left;
        }

        ret = curr = s.top();
        s.pop();

        while(next = nextNode(curr)){
            curr->right = next;
            next->left = curr;
            curr = next;
        }

        ret->left = curr;
        curr->right = ret;
        return ret;
    }
};
