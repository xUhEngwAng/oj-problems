#include <vector>
#include <cstdio>
#include <set>
using namespace std;

vector<vector<int>> inedge;

int main(){
	int N, M, one, two;
	scanf("%d %d", &N, &M);
	inedge = vector<vector<int>>(N + 1);
	for(int ix = 0; ix != M; ++ix){
		scanf("%d %d", &one, &two);
		inedge[two].push_back(one);
	}

	set<int> prev;
	vector<int> res;
	int K, curr;
	bool flag;
	scanf("%d", &K);
	for(int jx = 0; jx != K; ++jx){
		flag = true;
		for(int ix = 0; ix != N; ++ix){
			scanf("%d", &curr);
			if(!flag) continue;
			for(int e : inedge[curr])
				if(prev.find(e) == prev.end()){
					flag = false;
					break;
				}
			prev.insert(curr);
		}
		if(!flag) res.push_back(jx);
		prev.clear();
	}
	printf("%d", res[0]);
	for(int ix = 1; ix != res.size(); ++ix)
		printf(" %d", res[ix]);
	printf("\n");
	return 0;
}
