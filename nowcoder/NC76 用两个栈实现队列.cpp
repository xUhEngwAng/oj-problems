class Solution
{
public:
    void push(int node) {
        stack1.push(node);
    }

    int pop() {
        int tmp;
        if(stack2.empty()){
            while(!stack1.empty()){
                tmp = stack1.top();
                stack1.pop();
                stack2.push(tmp);
            }
        }
        int ret = stack2.top();
        stack2.pop();
        return ret;
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};