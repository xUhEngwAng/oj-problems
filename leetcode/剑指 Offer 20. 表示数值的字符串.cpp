/*
 * 题解是用有限状态自动机写的，看了一下感觉挺麻烦的。我这个解法至少
 * 思路非常清晰，编码上没啥难度，改了一些边界调节就 ac 了。
 */

class Solution {
public:
    bool isDigit(string s){
        int pos = 0, len = s.length();
        if(s[pos] == '+' || s[pos] == '-') ++pos;
        if(pos == len) return false;
        for(; pos != len; ++pos){
            if(!isdigit(s[pos])) return false;
        }
        return true;
    }

    bool isDecimal(string s){
        int start = 0, pos = s.find('.'), len = s.length();
        if(pos == string::npos) return false;
        if(s[start] == '+' || s[start] == '-') start += 1;
        if(start == pos && pos == len - 1) return false;
        for(int ix = start; ix != pos; ++ix){
            if(!isdigit(s[ix])) return false;
        }
        for(int ix = pos + 1; ix != len; ++ix){
            if(!isdigit(s[ix])) return false;
        }
        return true;
    }

    bool isNumber(string s) {
        int len = s.length();
        int start = 0, end = s.length()-1;
        while(start < len && s[start] == ' ') ++start;
        while(0 <= end && s[end] == ' ') --end;
        if(end < start) return false;
        string first, second;
        int pos = s.find_first_of("eE", start);
        if(pos != string::npos){
            first = s.substr(start, pos - start);
            second = s.substr(pos + 1, end - pos);
            if(!isDigit(first) && !isDecimal(first)) return false;
            if(!isDigit(second)) return false;
        }else{
            first = s.substr(start, end - start + 1);
            if(!isDigit(first) && !isDecimal(first)) return false;
        }
        return true;
    }
};
