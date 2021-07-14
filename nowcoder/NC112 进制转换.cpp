class Solution {
public:
    /**
     * 进制转换
     * @param M int整型 给定整数
     * @param N int整型 转换到的进制
     * @return string字符串
     */
    char toChar(int digit){
        if(digit < 10) return digit + '0';
        return digit - 10 + 'A';
    }
    
    string solve(int M, int N) {
        // write code here
        string ret;
        bool flag = false;
        if(M < 0){
            flag = true;
            M = -M;
        }
        while(M){
            ret.push_back(toChar(M % N));
            M = M / N;
        }
        if(flag) ret.push_back('-');
        reverse(ret.begin(), ret.end());
        return ret;
    }
};
