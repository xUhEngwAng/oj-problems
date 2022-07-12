/*
 * 此题我是尝试了两种思路，解法都不是很好。第一种解法是用一维的 dp，
 * dp[ix] 表示以 arr[ix] 结尾的最长斐波那契子序列的长度，dp[ix+1]
 * 只需查询所有前面的 dp[jx] 即可更新。然而这种解法是错误的，因为
 * dp[ix+1] 未必只依赖前面最长的斐波那契子序列。
 *
 * 然后就写了暴力解，遍历所有的起始位置 ix, jx，两个起始位置可以唯一
 * 确定一个斐波那契子序列。后面的元素使用二分查找，不出意外这个解法
 * 运行时间很慢。
 *
 * 最后看了一下标准题解，是用了二维 dp，使用 dp[i][j] 表示最后两个
 * 位置为 i, j 的最长斐波那契子序列，k = Index(arr[j] - arr[i])，
 * 
 * dp[i][j] = dp[k][i] + 1
 * 
 * 建立了一个 element 到 index 的哈希表，O(1) 的时间就可以对dp[i][j]
 * 进行更新，整体时间复杂度为 O(n^2)。
 *
 * 看完这个解法后，我又 revisit 下我的第二个暴力解，发现只要把二分
 * 查找替换成 hash 表的查找，两个解法就是差不多的，时间复杂度也是
 * O(n^2)。这是因为后续每一个元素的查找，本质上都是填写 dp[i][j]，
 * 这样的组合至多有 O(n^2) 个。修改后运行时间快了很多。
 *
 * 这个题也是暴露了不少问题：
 * 1. 我不擅长二维乃至多维的 dp，思路上不倾向于往这里想；
 * 2. 建立从元素值到元素索引的方法非常有效。
 */

class Solution {
public:
    int lenLongestFibSubseq(vector<int>& arr) {
        int n = arr.size(), sum, pos, maxlen = 0, currlen, prevprev, prev;
        unordered_set<int> hash;

        for(int ix = 0; ix != n; ++ix){
            hash.insert(arr[ix]);
        }
        
        for(int ix = 0; ix != n-2; ++ix){
            for(int jx = ix+1; jx != n-1; ++jx){
                prevprev = arr[ix], prev = arr[jx];
                currlen = 2;
                while(true){
                    sum = prevprev + prev;
                    if(hash.find(sum) == hash.end()) break;
                    currlen += 1;
                    prevprev = prev;
                    prev = sum;
                }
                if(maxlen < currlen) maxlen = currlen;
            }
        }

        return maxlen == 2? 0: maxlen;
    }
};
