#include <queue>
#include <vector>
#include <cstdio>
#include <cstdlib>
using namespace std;

int main(){
	int N, M, num, curr, child;
	scanf("%d %d", &N, &M);
	vector<vector<int>> tree(N + 1);
	for(int ix = 0; ix != M; ++ix){
		scanf("%d %d", &curr, &num);
		while(num--){
			scanf("%d", &child);
			tree[curr].push_back(child);
		}
	}

	int maxCount = 0, count = 1, nextCount = 0;
	int currLevel = 1, maxLevel;
	queue<int> q;
	q.push(1);
	while(!q.empty()){
		if(count > maxCount){
			maxLevel = currLevel;
			maxCount = count;
		}
		while(count--){
			curr = q.front();
			q.pop();
			for(int e : tree[curr])
				q.push(e);
			nextCount += tree[curr].size();
		}
		count = nextCount;
		nextCount = 0;
		++currLevel;
	}
	printf("%d %d\n", maxCount, maxLevel);
	return 0;
}
