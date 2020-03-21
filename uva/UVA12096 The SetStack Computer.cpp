#include <cstdio>
#include <string>
#include <stack>
#include <map>
#include <set>
using namespace std;

/*
 * 这个题兜兜转转终于通过了！一开始做的时候完全没有思路，想的是
 * 用 string 来表示每一个 set of set，但是这样做的开销非常大，
 * 因为这里的 string 可能会很长很长。
 *
 * 后来的想法是对于集合里的每一个元素都用 int 来代表，栈式计算机
 * 存在五种基本操作，其中只有 ADD 操作会产生新的元素，此时需要
 * 查看是否已经为集合 A 分配过了 id，否则则为它分配新的 id，随后
 * 将其 id 插入到集合 B 中即可。
 *
 * 我这里的实现还是比较愚蠢的，比如说仍然是将一个集合转换成string
 * 以后再与 id 建立映射的，实际上直接用 set<int> 也是可以作为 map
 * 的键值（只是我当时不知道）
 *
 * 此前的代码还存在一个bug，是在 Intersection 操作中，我的实现
 * 依次取出集合 A 的每一个元素，判断它是否在 B 中存在，否则将
 * 该元素在集合 A 中删除。由于在 foreach 遍历中删除元素，会产生
 * 一些奇怪的问题，正确的实现应该是将两个集合都存在的元素插入到
 * 一个新的集合当中。
 */

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
    set<int> tmp1, tmp2, tmp;
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
                    tmp.clear();
                    for(int e : tmp1)
                        if(tmp2.find(e) != tmp2.end())
                            tmp.insert(e);
                    s.push(tmp);
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
