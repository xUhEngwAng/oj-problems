#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

/*
 * 本题我一开始的写法就是滑动窗口，但是在一些细节的处理不
 * 够好，导致代码逻辑看起来很混乱，而且运行时间也比较差。
 * 实际上，此题并不需要每次循环更新最高的字符的频次，只有
 * 在出现更高频次时才进行更新，这样内部循环就可以省去一次
 * 对全部字符频次的遍历，时间上快了6倍左右。
 *
 * 这是因为，只有在新的字符和最高频次字符不一样时，才可能
 * 将窗口的左边向右移动，此时保存的最高字符频次可能高于实
 * 际值。但无论如何，只有在出现更高的字符频次时，滑动窗口
 * 的宽度才可能增大，因此不更新最高频次并不会对结果的正确
 * 性产生影响。
 */

class Solution {
public:
    int characterReplacement(string s, int k) {
        int left = 0, right = 0, n = s.length(), max = 0;
        vector<int> chcnt(26, 0);

        while(right < n){
            int ch = s[right] - 'A';
            chcnt[ch]++;
            if(max < chcnt[ch]) max = chcnt[ch];
            if(max + k < right - left + 1){
                chcnt[s[left]-'A']--;
                ++left;
            }
            ++right;
        }

        return n < max + k?n: max + k;
    }

    int characterReplacement_slow(string s, int k) {
        unordered_map<char, int> cnt;
        int max, ret = 0;
        for(int begin = 0, end = 0; begin != s.length(); ++begin){
            while(end != s.length()){
                cnt[s[end]]++;
                max = 0;
                for(auto e : cnt){
                    if(max < e.second)
                        max = e.second;
                }
                if(max + k < end - begin + 1){
                    cnt[s[end]]--;
                    break;
                }
                ++end;
            }
            if(ret < end - begin)
                ret = end - begin;
            cnt[s[begin]]--;
        }

        return ret;
    }
};

int main(){
    string str;
    int k;
    cin >> str >> k;

    Solution solution;
    int ans = solution.characterReplacement(str, k);
    cout << "The answer is " << ans << endl;
    return 0;
}
