class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int> numbers) {
        int curr_num, curr_count = 0;
        
        for(int ix = 0; ix != numbers.size(); ++ix){
            if(curr_count == 0) 
                curr_num = numbers.at(ix);
            if(numbers.at(ix) == curr_num) 
                curr_count += 1;
            else 
                curr_count -= 1;
        }
        
        return curr_num;
    }
};
