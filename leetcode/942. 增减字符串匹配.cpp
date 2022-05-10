#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
 * 这个题我的解法竟然是个二分，把原始 s 划分为两个部分，
 * 根据划分点是 I 还是 D 决定两个部分的取值范围，确保两
 * 部分的取值不会 overlap，然后递归地求解两个子部分。一
 * 开始的实现中还会 explicitly 合并两个部分的结果，这使
 * 复杂度上升到了 O(nlogn)。如果使用一个全局的 res 数组
 * 可以将复杂度降低到 O(n)。
 *
 * 结果这个题可以用贪心来解，写起来非常简单。本来我也想
 * 到这个办法了，但是感觉贪心可能导致后续的选择无解，实
 * 际上这种情况不会发生。
 */

class Solution {
public:
    vector<int> diStringMatch(string s) {
        vector<int> ret;
        ret.resize(s.length() + 1);
        StringMatch(s, ret, 0, s.length(), 0);
        return ret;
    }

    void StringMatch(const string& s, vector<int>& res, int begin, int end, int bias){
        if(begin == end){
            res[begin] = bias;
            return;
        }
        
        int mid = (begin + end) >> 1, left_bias, right_bias;
        if(s[mid] == 'I'){
            left_bias = bias;
            right_bias = bias + mid - begin + 1;
        }else{
            left_bias = bias + end - mid;
            right_bias = bias;
        }
        StringMatch(s, res, begin, mid, left_bias);
        StringMatch(s, res, mid+1, end, right_bias);
    }
};

int main(){
    string s;
    getline(cin, s);
    Solution solution;
    vector<int> res = solution.diStringMatch(s);
    for(int ix = 0; ix != res.size(); ++ix)
        cout << res[ix] << ' ' ;
    cout << endl;
    return 0;
}

