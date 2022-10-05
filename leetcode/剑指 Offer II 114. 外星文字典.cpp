#include <queue>
#include <string>
#include <vector>
using std::queue;
using std::string;
using std::vector;

/*
 * 这个题各个部分单独拆开吧也就那样，但是糅合到一起确实就比较有
 * 难度了，本题的思路是利用单词间的顺序建立字符的有向图，然后对
 * 该有向图进行拓扑排序来获得外星文字典的字符序。
 *
 * 这里有几个需要注意的点：
 * 1. 比较单词顺序时，只需要比较 words[ix] 和 words[ix+1]，后面
 *    的序是不需要比较的，因为这些序在图中表现为相隔几代的子孙
 *    节点，不会带来关于序的额外信息；
 * 2. 建图的过程需要注意，因为单词比较过程中会出现重复的边，需要
 *    对这些信息去重；
 * 3. 有一个很恶心的 case，是 ["abc", "ab"]，完全脱离了拓扑排序
 *    的初衷，需要特判一下。
 */

class Solution {
public:
    vector<vector<int>> graph;
    vector<vector<bool>> mat;
    vector<int> inOrder;
    string ret;

    bool lessThan(const string& lh, const string& rh){
        int m = lh.length(), n = rh.length();
        int len = (m < n)? m : n, ix;

        for(ix = 0; ix != len; ++ix){
            if(lh[ix] == rh[ix]) continue;
            if(mat[lh[ix]-'a'][rh[ix]-'a']) break;
            mat[lh[ix]-'a'][rh[ix]-'a'] = true;
            graph[lh[ix]-'a'].push_back(rh[ix]-'a');
            inOrder[rh[ix]-'a'] += 1;
            break;
        }

        if(ix == len && n < m) return false;
        return true;
    }

    void topologySort(){
        int curr, cnt = 0;
        queue<int> q;

        for(int ix = 0; ix != inOrder.size(); ++ix){
            if(inOrder[ix] != -1) cnt++;
            if(inOrder[ix] == 0) q.push(ix);
        }

        while(!q.empty()){
            curr = q.front();
            q.pop();
            ret.push_back(curr+'a');

            for(auto entry : graph[curr]){
                if(--inOrder[entry] == 0)
                    q.push(entry);
            }
        }

        if(ret.length() != cnt)
            ret.clear();
    }

    string alienOrder(vector<string>& words) {
        graph.resize(26);
        inOrder.resize(26, -1);
        mat.resize(26, vector<bool>(26, false));
        int n = words.size();

        for(auto str : words){
            for(char ch : str){
                inOrder[ch-'a'] = 0;
            }
        }

        for(int ix = 0; ix != n-1; ++ix){
            if(!lessThan(words[ix], words[ix+1]))
                return "";
        }

        topologySort();
        return ret;
    }
};
