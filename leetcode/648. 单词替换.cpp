#include <string>
#include <vector>
using namespace std;

class TriNode {
public:
    bool isLeaf;
    vector<TriNode*> children;

    TriNode(): isLeaf(true) {
        children.resize(26, nullptr);
    }

    void append(char ch){
        children[ch - 'a'] = new TriNode();
        isLeaf = false;
    }
};

class Solution {
public:
    TriNode* root;

    string replaceWords(vector<string>& dictionary, string sentence) {
        string ret, prefix;
        buildTrie(dictionary);
        vector<string> splitted_words = split(sentence);

        for(auto word : splitted_words){
            prefix = matchTrie(word);
            if(!prefix.empty()) ret += prefix;
            else ret += word;
            ret += " ";
        }

        return ret.substr(0, ret.length() - 1);
    }

    vector<string> split(const string& sentence){
        vector<string> ret;
        int begin = 0, end;

        while(true){
            end = sentence.find(' ', begin);
            if(end == string::npos) break;
            ret.push_back(sentence.substr(begin, end-begin));
            begin = end + 1;
        }

        ret.push_back(sentence.substr(begin));
        return ret;
    }

    static bool cmp(const string& lhs, const string& rhs){
        return lhs.length() < rhs.length();
    }

    void buildTrie(vector<string>& dict){
        sort(dict.begin(), dict.end(), cmp);
        root = new TriNode();
        TriNode* curr;

        for(auto word : dict){
            curr = root;
            for(auto ch : word){
                if(curr->children[ch-'a'] == nullptr){
                    curr->append(ch);
                    curr = curr->children[ch-'a'];
                } else{
                    curr = curr->children[ch-'a'];
                    if(curr->isLeaf) break;
                }
            }
        }
    }

    string matchTrie(const string& word){
        string ret;
        TriNode* curr = root;

        for(auto ch : word){
            if(curr->children[ch-'a'] == nullptr) break;
            curr = curr->children[ch-'a'];
            ret.push_back(ch);
            if(curr->isLeaf) return ret;
        }

        ret.clear();
        return ret;
    }
};
