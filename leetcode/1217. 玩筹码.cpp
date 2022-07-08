class Solution {
public:
    int minCostToMoveChips(vector<int>& position) {
        int odd = 0, even = 0;

        for(int e : position){
            if(e & 1) odd += 1;
            else even += 1;
        }

        return (odd < even)? odd: even;
    }
};
