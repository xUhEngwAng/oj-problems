#include <queue>
#include <string>
#include <unordered_map>
#include <vector>
using std::pair;
using std::queue;
using std::string;
using std::unordered_map;
using std::vector;

/*
 * 这个题挺有意思的。我自己的解法就是暴力解，建图然后用 bfs 算最短路径，
 * 由于这里需要判断两两字符串之间的关系，因此时间复杂度为 O(n^2 * m)，
 * 其中 n 为单词的数量，m 为单词的长度。
 *
 * 看题解用了一种我没见过的方案，对于每一个单词，可以将其每一个位置替换
 * 成通配符 *，从而形成图中的虚拟节点，在原单词和虚拟节点之间构造一条边，
 * 后续还是同样使用 bfs 计算最短路径长度。这样建图时间复杂度降低到了 
 * O(n * m^2)，从结果来看确实观察到了运行时间快了不少，不过相应的空间
 * 消耗也显著增加了。
 */

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_map<string, vector<string>> graph;
        unordered_map<string, bool> visited;
        wordList.push_back(beginWord);
        string tmp;

        for(auto word : wordList){
            tmp = word;
            visited[word] = false;
            
            for(int ix = 0; ix != word.length(); ++ix){
                tmp[ix] = '*';
                graph[word].push_back(tmp);
                graph[tmp].push_back(word);
                tmp[ix] = word[ix];
            }
        }

        queue<pair<string, int>> q;
        q.push({beginWord, 1});

        while(!q.empty()){
            auto curr = q.front();
            q.pop();

            for(auto neighbor : graph[curr.first]){
                if(visited[neighbor]) continue;
                if(neighbor == endWord) return curr.second/2 + 1;
                visited[neighbor] = true;
                q.push({neighbor, curr.second+1});
            }
        }

        return 0;
    }
};
