class Solution {
public:
    /**
     * 
     * @param prices int整型vector 
     * @return int整型
     */
    int maxProfit(vector<int>& prices) {
        // write code here
        vector<int> increases;
        increases.resize(prices.size());
        for(int ix = 1; ix != increases.size(); ++ix){
            increases.at(ix) = prices[ix] - prices[ix-1];
        }
        int curr = 0, max = 0;
        for(int ix = 0; ix != increases.size(); ++ix){
            curr += increases[ix];
            if(curr > max) max = curr;
            if(curr < 0) curr = 0;
        }
        return max;
    }
};
