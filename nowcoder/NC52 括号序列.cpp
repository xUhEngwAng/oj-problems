class Solution {
public:
    /**
     * 
     * @param s string字符串 
     * @return bool布尔型
     */
    bool isValid(string s) {
        // write code here
        stack<char> st;
        
        for(char ch : s){
            if(ch == '(' || ch == '{' || ch == '[')
                st.push(ch);
            else{
                if(st.empty()) return false;
                if(ch == ')' && st.top() != '(') return false;
                if(ch == '}' && st.top() != '{') return false;
                if(ch == ']' && st.top() != '[') return false;
                st.pop();
            }
        }
        
        if(!st.empty()) return false;
        return true;
    }
};