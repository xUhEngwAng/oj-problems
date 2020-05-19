#include <cstdio>
#include <cstring>
#include <unordered_map>
using namespace std;
#define MIN(X, Y) ((X) < (Y)? (X): (Y))

int ans[10001][10001], pos;
int primes[65536], vis[65536];
unordered_map<int, int> curr;

void init(){
	pos = 0;
	memset(vis, 0, sizeof(vis));
	for(int ix = 2; ix != 65536; ++ix){
		if(!vis[ix]) primes[pos++] = ix;
		for(int jx = 0; jx != pos && primes[jx]*ix < 65536; ++jx){
			vis[ix * primes[jx]] = true;
			if(ix % primes[jx] == 0) break;
		}
	}
}

void decomp(int n, bool flag){
	int cnt;
	for(int ix = 0; ix != pos; ++ix){
		cnt = 0;
		while(n % primes[ix] == 0) {cnt++; n = n / primes[ix];}
		if(cnt)
			if(flag) curr[primes[ix]] += cnt;
			else     curr[primes[ix]] -= cnt;
		if(n == 1) break;
	}
	if(n != 1)
		if(flag) curr[n] += 1;
		else     curr[n] -= 1;
}

int compute(int N, int M, int P){
	ans[0][0] = 1 % P;
	ans[0][1] = 0;
	for(int ix = 1, jx; ix <= N; ++ix){
		ans[ix][0] = 1 % P;
		for(jx = 1; jx <= MIN(M, ix); ++jx)
			ans[ix][jx] = (ans[ix-1][jx] + ans[ix-1][jx-1]) % P;
		ans[ix][jx+1] = 0;
	}
	return ans[N][M];
}

void exgcd(int a, int b, long long &x, long long &y){
	if(b == 0){
		x = 1, y = 0;
		return;
	}
	exgcd(b, a % b, x, y);
	long long t = x;
	x = y;
	y = t - a / b * y;
}

long long inv(int n, int P){
	long long x, y;
	exgcd(n, P, x, y);
	x = (x % P + P) % P;
	return x;
}

int solve(int N, int M, int P){
	long long curr = 1 % P;
	for(int ix = 1; ix <= M; ++ix){
		//printf("%d\n", curr);
		curr = (((curr * (N - ix + 1)) % P) * inv(ix, P)) % P;
	}
	return curr;
}

int main(){
	freopen("1.out", "w", stdout);
	int T, N, M, P;	
	init();
	scanf("%d", &T);
	long long res;
	while(T--){
		scanf("%d %d %d", &N, &M, &P);
		if(N <= 10000 && M <= 10000)
			printf("%d\n", compute(N, M, P));
		else
			if((M << 1) > N) 
				printf("%d\n", solve(N, N - M, P));
			else
				printf("%d\n", solve(N, M, P));
		/*curr.clear();
		if((M << 1) > N) M = N - M;
		for(int ix = 1; ix <= M; ++ix){
			decomp(N - ix + 1, true);
			decomp(ix, false);
			//printf("ix = %d\n", ix);
		}
		//printf("tag");
		res = 1;
		for(auto it = curr.begin(); it != curr.end(); ++it){
			for(int ix = 0; ix != it->second; ++ix)
				res = (res * it->first) % P;
		}
		printf("%d\n", res);*/
	}
	return 0;
}
