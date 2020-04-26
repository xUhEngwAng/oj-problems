#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
#define MAXN (1 << 16)

int prime[MAXN], pos;
bool vis[MAXN];
vector<int> decomp;

void init(){
	pos = 0;
	memset(vis, 0, sizeof(vis));
	for(int ix = 2; ix != MAXN; ++ix){
		if(!vis[ix]) prime[pos++] = ix;
		for(int jx = 0; jx < pos && prime[jx]*ix < MAXN; ++jx){
			vis[prime[jx]*ix] = true;
			if(ix % prime[jx] == 0) break;
		}
	}
	/*for(int ix = 0; ix != pos; ++ix)
		printf("%d ", prime[ix]);
	printf("\n");*/
}

int main(){
	//freopen("1.out", "w", stdout);
	int N, cnt = 0, tmp;
	unsigned int res;
	init();
	while(scanf("%d", &N) == 1){
		if(N == 0) break;
		printf("Case %d: ", ++cnt);
		if(N == 1){
            printf("2\n");
            continue;
		}
		res = 0;
		decomp.clear();
		for(int ix = 0; N != 1 && ix != pos; ++ix){
			tmp = 1;
			while(N % prime[ix] == 0){
				tmp = tmp * prime[ix];
				N = N / prime[ix];
			}
			if(tmp != 1) decomp.push_back(tmp);
		}
		if(N != 1) decomp.push_back(N);
		for(int e: decomp)
            res += e;
		if(decomp.size() == 1) res += 1;
		printf("%u\n", res);
	}
	return 0;
}
