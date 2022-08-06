class CQueue {
public:
    stack<int> tail, head;

    CQueue() {

    }
    
    void appendTail(int value) {
        tail.push(value);
    }
    
    int deleteHead() {
        int ret = -1;
        if(head.empty()){
            while(!tail.empty()){
                head.push(tail.top());
                tail.pop();
            }
        }
        if(head.empty()) return -1;
        ret = head.top();
        head.pop();

        return ret;
    }
};

/**
 * Your CQueue object will be instantiated and called as such:
 * CQueue* obj = new CQueue();
 * obj->appendTail(value);
 * int param_2 = obj->deleteHead();
 */
