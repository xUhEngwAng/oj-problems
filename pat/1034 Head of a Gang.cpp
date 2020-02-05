#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/*
 * 这个题我纠结了好久，题目本身看起来是非常简单的，就做一个
 * 深度优先搜索就可以解决问题，但是我的主要问题在于不知道用
 * 什么样的数据结构来保存图，是用邻接矩阵还是邻接表，此外节
 * 点的关键码还是 string 类型的，是对 string 做一个 hash
 * 还是利用一个 map 来记录索引关系。我发现对于这种复杂结构
 * 的题目，我真的很不会做。
 * 
 * 最后是用一个非常复杂的 map<string, map<string, int>> 
 * 整体上用邻接表来存储边的信息，这里我对 map 的相关操作还
 * 很不熟悉，比如 map 元素的插入，通常是直接用
 *
 * graph[key] = value
 *
 * 就可以了，用 map.insert 参数是 pair，反而比较复杂。此外，
 * 就算某个键值不在 map 中，也可以使用 += 运算符，即
 *
 * graph[key] += value
 *
 * 此时，graph[key] 好像会被初始化为 0。
 *
 * 我此前还为每一条边都保存了一个 visited 字段，来记录它的
 * 访问信息，后来发现其实没有必要。因为无向图中，每条边都会被
 * 访问两次，最后得到的结果除以2即可。
 *
 * 我看《算法笔记》上面的题解，是用邻接矩阵来存储的，首先建立了
 * 从 string 到 int 的 map 信息，这里并不是传统的用 hashcode，
 * 而是手动利用两个 map，记录了它们的相互转换信息，比如我可以
 * 将读到的第一个 string 映射到 1，第二个映射到 2，以此类推。
 * 这样问题就简化了不少，可以学习学习。不过我对邻接矩阵向来是
 * 没有什么好感。
 */

struct vertex{
	map<string, int> edges;
	bool visited = false;
};

struct res{
    string head;
    int numofGang;

    res(string name, int num): head(name), numofGang(num){}

    bool operator<(const res& right){
        return head < right.head;
    }
};

map<string, vertex> graph;
int totalWeight, maxWeight, cnt;
string head;

void dfs(string root){
    ++cnt;
    graph[root].visited = true;
    int currWeight = 0;
    for(auto e : graph[root].edges){
        currWeight += e.second;
        totalWeight += e.second;
        if(!graph[e.first].visited)
            dfs(e.first);
    }
    if(currWeight > maxWeight){
        maxWeight = currWeight;
        head = root;
    }
}

int main(){
	int N, K, weight;
	string one, two;
	cin >> N >> K;
	for(int ix = 0; ix != N; ++ix){
		cin >> one >> two >> weight;
		if(graph.find(one) == graph.end())
			graph[one] = vertex();
		if(graph.find(two) == graph.end())
			graph[two] = vertex();
		/*
		if(graph[one].edges.find(two) == graph[one].edges.end())
			graph[one].edges[two] = weight;
		else graph[one].edges[two] += weight;
		if(graph[two].edges.find(one) == graph[two].edges.end())
			graph[two].edges[one] = weight;
		else graph[two].edges[one] += weight;
        */
		graph[one].edges[two] += weight;
        graph[two].edges[one] += weight;
	}
    /*
	for(auto entry : graph){
		cout << entry.first << ": ";
		for(auto edge : entry.second.edges){
			cout << edge.first << '(' << edge.second.weight << ')' << ' ';
		}
		cout << endl;
	}*/
	int num = 0;
	vector<res> heads;
    for(auto entry : graph){
        totalWeight = maxWeight = cnt = 0;
        if(!entry.second.visited){
            dfs(entry.first);
            totalWeight = totalWeight >> 1;
            if(cnt > 2 && totalWeight > K){
                ++num;
                heads.emplace_back(head, cnt);
            }
        }
    }

    sort(heads.begin(), heads.end());
    cout << num << endl;
    for(res e : heads)
        cout << e.head << ' ' << e.numofGang << endl;
	return 0;
}
