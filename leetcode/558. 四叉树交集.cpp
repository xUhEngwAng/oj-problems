/*
// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;
    
    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};
*/

class Solution {
public:
    Node* intersect(Node* quadTree1, Node* quadTree2) {
        if(quadTree1->isLeaf) return quadTree1->val? quadTree1: quadTree2;
        if(quadTree2->isLeaf) return quadTree2->val? quadTree2: quadTree1;

        Node* top_left  = intersect(quadTree1->topLeft, quadTree2->topLeft);
        Node* top_right = intersect(quadTree1->topRight, quadTree2->topRight);
        Node* bottom_left  = intersect(quadTree1->bottomLeft, quadTree2->bottomLeft);
        Node* bottom_right = intersect(quadTree1->bottomRight, quadTree2->bottomRight);

        if(top_left->isLeaf && top_right->isLeaf && bottom_left->isLeaf && bottom_right->isLeaf && 
           top_left->val == top_right->val && top_right->val == bottom_left->val && bottom_left->val == bottom_right->val){
            return new Node(top_left->val, true);
        }

        return new Node(false, false, top_left, top_right, bottom_left, bottom_right);
    }
};
