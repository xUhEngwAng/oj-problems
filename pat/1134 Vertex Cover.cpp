#include <vector>
#include <cstdio>
#include <set>
using namespace std;

int main(){
	int N, M, one, two;
	scanf("%d %d", &N, &M);
	vector<vector<int>> graph(N);
	for(int ix = 0; ix != M; ++ix){
		scanf("%d %d", &one, &two);
		graph[one].push_back(two);
	}
	int K, num;
	scanf("%d", &K);
	bool flag;
	set<int> vertset;
	while(K--){
		scanf("%d", &num);
		vertset.clear();
		while(num--){
			scanf("%d", &one);
			vertset.insert(one);
		}
		flag = true;
		for(int ix = 0; ix != N; ++ix){
			if(vertset.find(ix) != vertset.end())
				continue;
			for(int e: graph[ix])
				if(vertset.find(e) == vertset.end()){
					flag = false;
					goto end;
				}
		}
		end:
		if(flag) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
