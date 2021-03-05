class Solution {
public:
    vector<string> ret;
    vector<bool> visited;
    string tmp;
    
    void dfs(int start, const string& str){
        char prev = '-';
        visited[start] = true;
        tmp.push_back(str[start]);
        if(tmp.size() == str.size()){
            ret.push_back(tmp);
            goto next;
        }
        
        for(int ix = 0; ix != str.size(); ++ix){
            if(visited[ix] || str[ix] == prev) continue;
            dfs(ix, str);
            prev = str[ix];
        }
        
        next:
        tmp.pop_back();
        visited[start] = false;
    }
    
    vector<string> Permutation(string str) {
        sort(str.begin(), str.end());
        visited.resize(str.size(), false);
        char prev = '-';
        
        for(int ix = 0; ix != str.size(); ++ix){
            if(str[ix] == prev) continue;
            dfs(ix, str);
            prev = str[ix];
        }
        
        return ret;
    }
};