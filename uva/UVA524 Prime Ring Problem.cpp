#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

int n;
vector<int> seq;
vector<bool> visited;

bool isPrime(int num){
	for(int ix = 2; ix <= sqrt(num + 0.5); ++ix)
		if(num % ix == 0) return false;
	return true;
}

void dfs(int curr){
	seq.push_back(curr);
	visited[curr] = true;

	if(seq.size() == n){
		if(isPrime(seq.back() + 1)){
			printf("%d", seq[0]);
			for(int ix = 1; ix != seq.size(); ++ix)
				printf(" %d", seq[ix]);
			printf("\n");
		}
		goto ret;
	}

	for(int ix = 2; ix <= n; ++ix)
		if(!visited[ix] && isPrime(curr + ix))
			dfs(ix);

	ret:
	visited[curr] = false;
	seq.pop_back();
}

int main(){
	int cnt = 0;
	while(scanf("%d", &n) == 1){
		if(cnt != 0) printf("\n");
		printf("Case %d:\n", ++cnt);
		visited.resize(n);
		dfs(1);
	}
	return 0;
}
