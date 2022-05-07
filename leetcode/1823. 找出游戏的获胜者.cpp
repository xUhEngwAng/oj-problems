#include <iostream>
#include <vector>
using namespace std;

/*
 * 这个题算是比较有意思了。一开始我是写了个 O(n^2)
 * 的解法，总而言之就是模拟了游戏的整个过程，每次把
 * 输掉的小伙伴移除出数组。
 *
 * 实际上这个题可以使用动态规划来解。设 f(n, k) 为
 * n 个小伙伴时最终获胜的那个小伙伴，为了得到 f(n, k)
 * 可以先选出第一步被淘汰的小伙伴，即 k，随后对于剩
 * 下的 n-1 个小伙伴，可知获胜者为 f(n-1, k)。但此
 * 时的位置偏移了 k 位，因此实际的获胜者为
 * 
 * f(n, k) = (f(n-1, k) + k - 1) % n + 1
 *
 * 这里的 -1 和 +1 是为了补偿取余后的范围在 [0, n) 之间。
 */

class Solution {
public:
    int findTheWinner(int n, int k){
        int curr = 1;

        for(int ix = 2; ix <= n; ++ix)
            curr = (curr + k - 1) % ix + 1;

        return curr;
    }

    int findTheWinner_(int n, int k) {
        // O(n^2) solution
        vector<int> remaining;
        remaining.reserve(n);

        for(int ix = 1; ix <= n; ++ix)
            remaining.push_back(ix);

        int curr = 0;

        while(n > 1){
            curr = (curr + k - 1) % n;
            cout << remaining[curr] << " is out." << endl;
            remaining.erase(remaining.begin() + curr); 
            --n;
        }

        return remaining[0];
    }
};

int main(){
    int n, k;
    cin >> n >> k;
    Solution solution;
    int ans = solution.findTheWinner(n, k);
    cout << "The answer is " << ans << endl;
    return 0;
}
