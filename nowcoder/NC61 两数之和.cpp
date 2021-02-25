#include <unordered_map>

class Solution {
public:
    /**
     * 
     * @param numbers int整型vector 
     * @param target int整型 
     * @return int整型vector
     */
    vector<int> twoSum(vector<int>& numbers, int target) {
        // write code here
        unordered_map<int, int> hash;
        int curr, comp, ix;
        
        for(ix = 0; ix != numbers.size(); ++ix){
            curr = numbers[ix];
            comp = target - curr;
            if(hash.find(comp) != hash.end()) break;
            hash[curr] = ix;
        }
        
        return vector<int>({hash[comp] + 1, ix + 1});
    }
};