class Solution {
public:
    vector<vector<int>> ret;
    vector<int> tmp;
    vector<bool> visited;
    
    void dfs(int start, const vector<int>& num){
        visited[start] = true;
        tmp.push_back(num[start]);
        int cnt = 0, prev = 0x7fffffff;
        
        for(int ix = 0; ix != num.size(); ++ix){
            if(!visited[ix] && num[ix] != prev){
                dfs(ix, num);
                prev = num[ix];
                cnt += 1;
            }
        }
        
        if(cnt == 0)
            ret.push_back(tmp);
        
        tmp.pop_back();
        visited[start] = false;
   }
    
    vector<vector<int>> permuteUnique(vector<int> &num) {
        sort(num.begin(), num.end());
        visited.resize(num.size(), false);
        int prev = 0x7fffffff;
        
       for(int ix = 0; ix != num.size(); ++ix){
           if(num[ix] != prev){
               dfs(ix, num);
               prev = num[ix];
           }
       }
        
       return ret;
    }
};