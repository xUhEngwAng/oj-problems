#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> seq;
int *coins, M, N;

int dfs(int origin, int sum){
	sum += coins[origin];
	seq.push_back(coins[origin]);
	if(sum > M){
		seq.pop_back();
		return -1;
	}
	if(sum == M) return 1;

	int ret;
	for(int ix = origin + 1; ix <= N; ++ix){
		ret = dfs(ix, sum);
		if(ret == -1) break;
		if(ret == 1) return ret;
	}
	seq.pop_back();
	return 0;
}

int main(){
	scanf("%d %d", &N, &M);
	coins = new int[N + 1];
	coins[0] = 0;
	for(int ix = 1; ix <= N; ++ix)
		scanf("%d", coins + ix);
	sort(coins, coins + N + 1);
	int ret = dfs(0, 0);
	if(ret == 1){
		printf("%d", seq[1]);
		for(int ix = 2; ix != seq.size(); ++ix)
			printf(" %d", seq[ix]);
		printf("\n");
	}
	else
        printf("No Solution\n");
	return 0;
}
