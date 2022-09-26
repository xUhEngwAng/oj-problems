#define MAX(X, Y) ((X)<(Y)?(Y):(X))
#define MIN(X, Y) ((X)<(Y)?(X):(Y))

class Solution {
public:
    const int INF = 0x7fffffff;

    int maxProfit(vector<int>& prices) {
        int n = prices.size(), max_price = -INF, min_price = INF, ret = 0;
        vector<int> startat(n+1), endat(n+1);

        for(int ix = n-1; ix >= 0; --ix){
            max_price = MAX(max_price, prices[ix]);
            startat[ix] = MAX(startat[ix+1], max_price-prices[ix]);
        }

        for(int ix = 0; ix < n; ++ix){
            min_price = MIN(min_price, prices[ix]);
            endat[ix+1] = MAX(endat[ix], prices[ix]-min_price);
        }

        for(int ix = 0; ix != n; ++ix){
            ret = MAX(ret, startat[ix] + endat[ix+1]);
        }

        return ret;
    }
};
