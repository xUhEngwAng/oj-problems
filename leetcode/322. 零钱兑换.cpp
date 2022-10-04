#include <vector>
using std::vector;

/*
 * 这个题本来我不会写，连夜去看了看紫书，才发现原来是最原始的
 * DAG 上的动态规划，跟背包都没啥关系，之前一直在用背包的思路
 * 在想来着。我这里题解还写了个记忆化搜索，其实完全没有必要，
 * 因为 dp 数组更新的方向是比较明确的，自下而上的更新可能写起
 * 来更加简单，也少了函数堆栈的调用开销。
 */

class Solution {
public:
    vector<int> dp;
    const int INF = 0x7fffffff;

    int minCoins(const vector<int>& coins, long long curr, int amount){
        if(amount < curr) return -1;
        if(dp[curr] != -2) return dp[curr];
        int res, min = INF;
        
        for(auto coin : coins){
            res = minCoins(coins, curr+coin, amount);
            if(res != -1 && res < min) min = res;
        }

        dp[curr] = (min != INF)? min + 1 : -1;
        return dp[curr];
    }

    int coinChange(vector<int>& coins, int amount) {
        dp.resize(amount + 1, -2);
        dp[amount] = 0;
        return minCoins(coins, 0, amount);
    }
};
