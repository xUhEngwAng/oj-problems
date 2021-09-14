#define MIN(X, Y) ((X) < (Y)? (X): (Y))

class Solution {
public:
    int GetUglyNumber_Solution(int index) {
        if(index == 0) return 0;
        vector<int> ugly_numbers;
        int ix2 = 0, ix3 = 0, ix5 = 0, curr;
        ugly_numbers.push_back(1);
        for(int ix = 2; ix <= index; ++ix){
            curr = MIN(MIN(
                       ugly_numbers[ix2] * 2, 
                       ugly_numbers[ix3] * 3), 
                       ugly_numbers[ix5] * 5
                      );
            ugly_numbers.push_back(curr);
            if(curr == ugly_numbers[ix2] * 2) ix2 += 1;
            if(curr == ugly_numbers[ix3] * 3) ix3 += 1;
            if(curr == ugly_numbers[ix5] * 5) ix5 += 1;
        }
        return ugly_numbers.back();
    }
};
