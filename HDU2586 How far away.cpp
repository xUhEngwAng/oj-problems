#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

struct node{
	int id;
	int weight;
	node() = default;
	node(int i, int w): id(i), weight(w){}
};

vector<vector<node>> tree(40001);
node father[40001][16];
int  dep[40001];

void dfs(int curr, int parent, int weight){
	father[curr][0].id = parent;
	father[curr][0].weight = weight;
	dep[curr] = dep[parent] + 1;
	int temp;
	for(int ix = 1; ix != 16; ++ix){
		temp = father[curr][ix - 1].id;
		father[curr][ix].id = father[temp][ix - 1].id;
		father[curr][ix].weight = father[curr][ix - 1].weight + father[temp][ix - 1].weight;
	}
	for(auto e : tree[curr])
		if(dep[e.id] == 0)
			dfs(e.id, curr, e.weight);
    /*printf("curr: %d, depth: %d\n", curr, dep[curr]);
    for(int ix = 0; ix != 16; ++ix)
        if(father[curr][ix].id != 0)
            printf("%d %d\n", father[curr][ix].id, father[curr][ix].weight);*/
}

int lca(int one, int two){
	int ret = 0;
	if(dep[one] < dep[two]) swap(one, two);
	int diff = dep[one] - dep[two];
	for(int ix = 15; ix >= 0; --ix){
		if((1 << ix) & diff){
            ret += father[one][ix].weight;
			one = father[one][ix].id;
		}
	}
	if(one == two) return ret;
	for(int ix = 15; ix >= 0; --ix){
		if(father[one][ix].id != father[two][ix].id){
			one = father[one][ix].id;
			two = father[two][ix].id;
			ret += father[one][ix].weight + father[two][ix].weight;
		}
	}
	ret += father[one][0].weight + father[two][0].weight;
	return ret;
}

int main(){
	int t, n, m, one, two, dist;
	scanf("%d", &t);
	while(t--){
		scanf("%d %d", &n, &m);
		memset(father, 0, sizeof(node) * (n + 1) * 16);
		memset(dep, 0, sizeof(int) * (n + 1));
		for(int ix = 0; ix != n - 1; ++ix){
			scanf("%d %d %d", &one, &two, &dist);
			tree[one].emplace_back(two, dist);
			tree[two].emplace_back(one, dist);
		}
		dfs(1, 0, 0);
		while(m--){
			scanf("%d %d", &one, &two);
			printf("%d\n", lca(one, two));
		}
		//printf("\n");
		for(int ix = 1; ix <= n; ++ix)
			tree[ix].clear();
	}
	return 0;
}
