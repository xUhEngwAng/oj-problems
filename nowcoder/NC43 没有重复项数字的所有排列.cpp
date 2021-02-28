class Solution {
public:
    vector<bool> visited;
    vector<int> tmp;
    vector<vector<int>> ret;
    
    void dfs(int start, const vector<int> &num){
        visited[start] = true;
        tmp.push_back(num[start]);
        if(tmp.size() == num.size()){
            ret.push_back(tmp);
            goto next;
        }
        
        for(int ix = 0; ix != num.size(); ++ix){
            if(!visited[ix])
                dfs(ix, num);
        }
        
        next:
        tmp.pop_back();
        visited[start] = false;
    }
    
    vector<vector<int>> permute(vector<int> &num) {
        visited.resize(num.size(), false);
        
        for(int ix = 0; ix != num.size(); ++ix)
            dfs(ix, num);
        
        return ret;
    }
};