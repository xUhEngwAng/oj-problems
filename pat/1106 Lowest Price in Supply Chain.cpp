#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

vector<vector<int>> tree;
int count = 0, depth = 100001;

void dfs(int root, int currdepth){
	if(tree[root].empty()){
		if(currdepth < depth){
			depth = currdepth;
			count = 1;
		}else
		if(currdepth == depth) ++count;
		return;
	}
	for(int e : tree[root])
		dfs(e, currdepth + 1);
}

int main(){
	int N, num, child;
	double P, rate;
	scanf("%d %lf %lf", &N, &P, &rate);
	tree = vector<vector<int>>(N);
	for(int ix = 0; ix != N; ++ix){
		scanf("%d", &num);
		while(num--){
			scanf("%d", &child);
			tree[ix].push_back(child);
		}
	}

	dfs(0, 0);
	printf("%.4f %d\n", P * pow(1 + rate / 100, depth), count);
	return 0;
}
