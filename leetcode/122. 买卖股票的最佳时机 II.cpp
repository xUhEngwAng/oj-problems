class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int ret = 0, n = prices.size() - 1;

        for(int ix = 0; ix != n; ++ix){
            if(prices[ix] < prices[ix + 1])
                ret += prices[ix+1] - prices[ix];
        }

        return ret;
    }
};
