#include <cmath>
#include <vector>
using std::pow;
using std::vector;

/*
 * 这个题给我恶心坏了，优化了好多版本。一开始写了 dfs，为了不超时
 * 加了各种剪枝，还利用了最终结果的对称性，结果 n=11 还是超时了。
 *
 * 然后自己想到了动态规划的方法，dp[i][j] 表示 i 个骰子和为 j 的
 * 方案数，可惜写的是个二维数组，空间复杂度有点高。这个 dp 其实每
 * 次只依赖第 i-1 维的状态，完全可以只保存两个一维数组，可以进一步
 * 优化空间复杂度。
 *
 * 之后又做了一个优化，原始 dp 计算的是方案的个数，其实可以直接算
 * 每个值出现的概率，本质上就是一个全概率公式。但是我的这个写法边界
 * 条件判断比较多，代码看起来不太好懂，这个题目下最火的题解比我好多
 * 了。
 */

class Solution {
public:
    int sum, res;

    void dfs(int target, int n, int pos, int curr){
        sum += curr;

        if(n == pos){
            if(target == sum) res += 1;
            goto end;
        }
        if(target <= sum) goto end;
        if(sum+6*(n-pos)<target) goto end;

        for(int ix = 1; ix <= 6; ++ix)
            dfs(target, n, pos+1, ix);

        end:
        sum -= curr;
    }

    vector<double> dicesProbability(int n) {
        vector<double> curr(6, 1.0/6);

        for(int ix = 2; ix <= n; ++ix){
            vector<double> next;
            for(int target = ix; target <= 6 * ix; ++target){
                double tmp = 0;
                for(int jx = 1; jx <= 6; ++jx){
                    if(target-jx-ix+1 < 0) break;
                    if(target-jx > 6*ix-6) continue;
                    tmp += curr[target-jx-ix+1] / 6.0;
                }
                next.push_back(tmp);
            }
            curr = next;
        }

        return curr;
    }
};
