/*
 * 这个题我的做法比较愚蠢，是针对前缀和后缀分别建了一个键树。在查询
 * 的时候，分别查询两个键树，然后取它们的交集。显而易见，在最坏情况
 * 下这个方法和暴力解的复杂度并没有什么区别，空间还消耗更多。
 *
 * 答案的题解是让我觉得比较巧妙的，是将前缀和后缀同时用于建立键树，
 * 比如 apple 建立的树就是 {a, e}, {p, l}, {p, p} 这样。需要注意的
 * 是还要考虑到查询时前缀和后缀长度不同的情况，因此应该使用一个特殊
 * 字符来表示这种情况，查询时也使用同样的特殊字符。这里建树的逻辑也
 * 有一些 tricky，感觉这个题确实值得 hard。
 *
 * 另一个解法是把所有前缀后缀组合遍历，然后保存在一个哈希表里面。这
 * 个方法本质上和上一个方法没有区别，只是在初始化的内循环，需要做
 * 字符串 concat，因此在时间复杂度上多乘了一个字符串的长度。我是觉得
 * 我之前分析复杂度的时候从来不会分析这么细，但是这里的这个常数对
 * 性能的影响可能还挺明显的，实际上上一个方法确实快 30% ~ 50%。
 */

class WordFilter {
public:
    unordered_map<string, int> hash;

    WordFilter(vector<string>& words) {
        string prefix, suffix, key, word;
        int n = words.size(), m;

        for(int pos = n-1; pos >= 0; --pos){
            word = words[pos];
            m = word.length();

            for(int i = 1; i <= m; i++){
                prefix = word.substr(0, i);
                for(int j = 1; j <= m; ++j){
                    suffix = word.substr(m-j, j);
                    key = prefix + "-" + suffix;
                    if(hash.count(key)) continue;
                    hash[key] = pos;
                }
            }
        }
    }
    
    int f(string pref, string suff) {
        string key = pref + "-" + suff;
        auto it = hash.find(key);
        if(it == hash.end()) return -1;
        return it->second;
    }
};

/* version two: take advantage of a trie*/

class TriNode {
public:
    int index;
    unordered_map<int, TriNode*> children;

    TriNode(): index(-1) {}
    TriNode(int ix): index(ix) {}
};

class WordFilter {
public:
    TriNode* root;

    WordFilter(vector<string>& words) {
        int n = words.size();
        root = new TriNode();
        for(int ix = n-1; ix >= 0; --ix)
            appendword(root, words[ix], ix);
    }

    void appendword(TriNode* root, const string& word, int index){
        int m = word.length();
        TriNode *curr = root, *temp;
        int key;

        for(int ix = 0; ix != m; ++ix){
            key = word[ix] * 128 + word[m-1-ix];
            if(!curr->children.count(key))
                curr->children[key] = new TriNode(index);
            curr = curr->children[key];
            
            temp = curr;
            for(int jx = ix + 1; jx != m; ++jx){
                key = word[jx] * 128 + '*';
                if(!temp->children.count(key))
                    temp->children[key] = new TriNode(index);
                temp = temp->children[key];
            }

            temp = curr;
            for(int jx = ix + 1; jx != m; ++jx){
                key = '*' * 128 + word[m-1-jx];
                if(!temp->children.count(key))
                    temp->children[key] = new TriNode(index);
                temp = temp->children[key];
            }
        }
    }
    
    int f(string pref, string suff) {
        int m = pref.length(), n = suff.length();
        TriNode* curr = root;
        int key;

        for(int ix = 0; ix < m || ix < n; ++ix){
            key = (ix < m? pref[ix]: '*');
            key = key * 128 + (ix < n? suff[n-1-ix]: '*');
            if(!curr->children.count(key)) return -1;
            curr = curr->children[key];
        }

        return curr->index;
    }
};

/**
 * Your WordFilter object will be instantiated and called as such:
 * WordFilter* obj = new WordFilter(words);
 * int param_1 = obj->f(pref,suff);
 */
