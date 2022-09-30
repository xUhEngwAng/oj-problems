class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> s;
        int push_pos = 0, pop_pos = 0;

        while(true){
            while(!s.empty() && s.top() == popped[pop_pos]){
                pop_pos += 1;
                s.pop();
            }
            if(push_pos == pushed.size()) break;
            s.push(pushed[push_pos]);
            push_pos += 1;
        }

        return s.empty();
    }
};
