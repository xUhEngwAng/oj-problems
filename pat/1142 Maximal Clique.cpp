#include <vector>
#include <cstdio>
#include <set>
using namespace std;

/*
 * 写一下这个题的基本思路。
 *
 * 数据结构方面是用邻接表来存储整张图，每个节点的邻居节点用
 * set 组织起来，方面后续的查找。对于每一个 query，管理一个
 * neighbors 集合来保存已经读入的节点的邻居节点的交集。
 *
 * 对于每个读入的节点，首先判断它是否在 neighbors 当中，否
 * 则说明当前集合并非是一个 Clique；如果对于所有节点上面的
 * 条件都成立，则说明是一个 Clique，接着借助 neighbors 的
 * 规模来判断是否是最大的 Clique：如果 neighbors 非空，说
 * 明还存在集合外的其他节点，与集合内的所有节点都是邻居，则
 * 当前 Clique 并非最大的。
 */

int main(){
	int N, M, one, two;
	scanf("%d %d", &N, &M);
	vector<set<int>> graph(N + 1);
	for(int ix = 0; ix != M; ++ix){
		scanf("%d %d", &one, &two);
		graph[one].insert(two);
		graph[two].insert(one);
	}
	int K;
	bool flag;
	scanf("%d", &K);
	set<int> neighbors;
	while(K--){
		scanf("%d %d", &M, &one);
		neighbors = graph[one];
		flag = true;
		while(--M){
			scanf("%d", &two);
			if(!flag) continue;
			if(neighbors.find(two) == neighbors.end())
				flag = false;
			else
				for(int e : neighbors)
					if(graph[two].find(e) == graph[two].end())
						neighbors.erase(e);
		}
		if(!flag) printf("Not a Clique\n");
		else
		if(neighbors.empty()) printf("Yes\n");
		else printf("Not Maximal\n");
	}
	return 0;
}
