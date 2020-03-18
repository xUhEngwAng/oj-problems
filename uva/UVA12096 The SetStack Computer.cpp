#include <cstdio>
#include <string>
#include <stack>
#include <map>
#include <set>
using namespace std;

stack<set<int>> s;
map<string, int> m;

string tostr(const set<int> &input){
    string res = "{";
    for(int e : input){
        res.push_back(e + '0');
        res.push_back(',');
    }
    return res;
}

int main(){
    int T, N, cnt, curr;
    char input[10];
    string hash;
    set<int> tmp1, tmp2;
    scanf("%d", &T);
    while(T--){
        scanf("%d", &N);
        while(!s.empty()) s.pop();
        m.clear();
        cnt = 0;
        while(N--){
            scanf("%s", input);
            if(input[0] == 'P') s.push(set<int>());
            else
            if(input[0] == 'D') s.push(s.top());
            else{
                tmp1 = s.top();
                s.pop();
                tmp2 = s.top();
                s.pop();
                if(input[0] == 'U'){
                    for(int e : tmp2)
                        tmp1.insert(e);
                    s.push(tmp1);
                }
                else
                if(input[0] == 'I'){
                    for(int e : tmp1)
                        if(tmp2.find(e) == tmp2.end())
                            tmp1.erase(e);
                    s.push(tmp1);
                }
                else{
                    hash = tostr(tmp1);
                    if(m.find(hash) == m.end())
                        m[hash] = cnt++;
                    curr = m[hash];
                    tmp2.insert(curr);
                    s.push(tmp2);
                }
            }
            printf("%d\n", s.top().size());
        }
        printf("***\n");
    }
    return 0;
}
