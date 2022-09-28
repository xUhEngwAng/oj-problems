#include <vector>
#include <stack>
using std::vector;
using std::stack;

class MinStack {
public:
    vector<int> s;
    stack<int> min_stack;

    /** initialize your data structure here. */
    MinStack() {    
        
    }
    
    void push(int x) {
        s.push_back(x);
        if(min_stack.empty() || x <= min_stack.top())
            min_stack.push(x);
    }
    
    void pop() {
        int val = s.back();
        s.pop_back();
        if(val == min_stack.top())
            min_stack.pop();
    }
    
    int top() {
        return s.back();
    }
    
    int min() {
        return min_stack.top();
    }
};
