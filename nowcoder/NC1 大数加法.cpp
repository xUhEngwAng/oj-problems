class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     * 计算两个数之和
     * @param s string字符串 表示第一个整数
     * @param t string字符串 表示第二个整数
     * @return string字符串
     */
    string solve(string s, string t) {
        // write code here
        int m = s.length(), n = t.length();
        int carry = 0, one, two, res;
        string ret;

        for(int i = m - 1, j = n - 1; i >= 0 || j >= 0; i--, j--){
            one = (i >= 0? s[i]-'0': 0);
            two = (j >= 0? t[j]-'0': 0);
            res = one + two + carry;
            if(res >= 10){
                res -= 10;
                carry = 1;
            }else{
                carry = 0;
            }
            ret.push_back(res + '0');
        }

        if(carry){
            ret.push_back('1');
        }

        reverse(ret.begin(), ret.end());
        return ret;
    }
};
