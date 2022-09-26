#define MIN(X, Y) ((X)<(Y)?(X):(Y))

class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        int prevRed = 0, prevBlue = 0, prevGreen = 0;
        int currRed, currBlue, currGreen;
        for(int ix = 0; ix != costs.size(); ++ix){
            currRed = costs[ix][0] + MIN(prevBlue, prevGreen);
            currBlue = costs[ix][1] + MIN(prevRed, prevGreen);
            currGreen = costs[ix][2] + MIN(prevRed, prevBlue);
            prevRed = currRed;
            prevBlue = currBlue;
            prevGreen = currGreen;
        }
        return MIN(currRed, MIN(currBlue, currGreen));
    }
};
