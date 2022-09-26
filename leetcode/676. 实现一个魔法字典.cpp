#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class TriNode {
public:
    vector<TriNode*> children;

    TriNode(){
        children.resize(26, nullptr);
    }
};

class MagicDictionary {
public:
    unordered_map<int, TriNode*> tri_forest; 

    MagicDictionary() {
    
    }
    
    void buildDict(vector<string> dictionary) {
        for(auto word : dictionary){
            appendForest(word);
        }
    }
    
    bool search(string searchWord) {
        int m = searchWord.length();
        if(tri_forest.find(m) == tri_forest.end())
            return false;
        TriNode* curr = tri_forest[m];
        return dfs(curr, searchWord, 0, 0); 
    }

    bool dfs(TriNode* root, const string& word, int pos, int cnt){
        if(cnt == 2) return false;
        if(pos == word.length()){ 
            if(cnt == 1) return true;
            return false;
        }

        bool res;
        char ch = word[pos];

        for(int ix = 0; ix != 26; ++ix){
            if(!root->children[ix]) continue;
            if(ch == ix + 'a')
                res = dfs(root->children[ix], word, pos + 1, cnt);
            else 
                res = dfs(root->children[ix], word, pos + 1, cnt+1);
            if(res) return true;
        }

    }

    void appendForest(const string& word){
        int m = word.length();
        if(tri_forest.find(m) == tri_forest.end())
            tri_forest[m] = new TriNode();
        TriNode* curr = tri_forest[m];

        for(char ch : word){
            if(!curr->children[ch-'a'])
                curr->children[ch-'a'] = new TriNode();
            curr = curr->children[ch-'a'];
        }
    }
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dictionary);
 * bool param_2 = obj->search(searchWord);
 */
