/*
 * 这题我不是很喜欢，感觉没啥意义。在真正稀疏的情况下，怎么做都是
 * O(n)，还不如一开始就暴力搜，或者打个表啥的。
 */

class Solution {
public:
    int findString(vector<string>& words, string s) {
        int begin = 0, end = words.size(), mid;

        while(begin < end){
            mid = (begin + end) >> 1;
            while(mid < end && words[mid] == "") ++mid;
            if(mid == end) end = (begin + end) >> 1;
            else if(s < words[mid]) end = mid;
            else if(words[mid] < s) begin = mid + 1;
            else return mid;
        }

        return -1;
    }
};
