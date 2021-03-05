#include <unordered_set>
#include <queue>

class Solution {
public:
    /**
     * 
     * @param arr int整型vector the array
     * @return int整型
     */
    int maxLength(vector<int>& arr) {
        // write code here
        unordered_set<int> hash;
        queue<int> q;
        int maxlen = 0, curr;
        
        for(int ix = 0; ix != arr.size(); ++ix){
            curr = arr[ix];
            if(hash.find(curr) == hash.end()){
                hash.insert(curr);
                q.push(curr);
                if(maxlen < q.size()) maxlen = q.size();
            }
            else{
                
                while(q.front() != curr){
                    hash.erase(q.front());
                    q.pop();
                }
                
                hash.erase(q.front());
                q.pop();
                hash.insert(curr);
                q.push(curr);
            }
        }
        
        return maxlen;
    }
};