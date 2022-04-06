#include <vector>
using std::vector;

#define MAX(X, Y) ((X) < (Y)? (Y): (X))
#define MIN(X, Y) ((Y) < (X)? (Y): (X))

/*
 * 这个题虽然是个easy，但是我却没有写出最优解......
 * 我的思路是，对于每个位置pos，预先求出它后面股票价格
 * 的最高点并保存下来，这样可以用O(n)的时间和空间解决。
 *
 * 同理，我们也可以计算每个位置之前股票价格的最低点，
 * 而最低点可以随着循环一起更新，就不需要额外的空间了。
 */

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int ret = 0, min_price = 0x7fffffff;

        for(int ix = 0; ix != prices.size(); ++ix){
            min_price = MIN(min_price, prices[ix]);
            ret = MAX(ret, prices[ix] - min_price);
        }

        return ret;
    }
};
