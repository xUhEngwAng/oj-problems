#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;
#define MAXN 10000
#define MIN(X, Y) ((X) < (Y)? (X): (Y))

int up[MAXN], down[MAXN], prime[MAXN], pos;
bool vis[10000];
vector<int> decomp[10000];

void init(){
	memset(vis, 0, sizeof(vis));
	pos = 0;
	for(int ix = 2; ix < 10000; ++ix){
		if(!vis[ix]) prime[pos++] = ix;
		for(int jx = 0; jx < pos && prime[jx]*ix < 10000; ++jx){
			vis[prime[jx] * ix] = true;
			if(ix % prime[jx] == 0) break;
		}
	}

	int tmp;
	for(int ix = 2; ix < 10000; ++ix){
		tmp = ix;
		for(int jx = 0; tmp != 1; ){
			if(tmp % prime[jx] == 0){
				tmp = tmp / prime[jx];
				decomp[ix].push_back(jx);
			}
			else ++jx;
		}
	}
	/*for(int ix = 9000; ix < 10000; ++ix){
		printf("%d = %d", ix, p[decomp[ix][0]]);
		for(int jx = 1; jx != decomp[ix].size(); ++jx)
			printf(" x %d", p[decomp[ix][jx]]);
		printf("\n");
	}*/
}

void decomposition(int fac, int *arr){
	for(int ix = 2; ix <= fac; ++ix){
		for(int e : decomp[ix])
			arr[e]++;
	}
}

int main(){
	int p, q, r, s, minimal;
	double res;
	init();
	while((scanf("%d %d %d %d", &p, &q, &r, &s)) == 4){
		memset(up, 0, sizeof(up));
		memset(down, 0, sizeof(down));
		decomposition(p, up);
		decomposition(s, up);
		decomposition(r-s, up);
		decomposition(q, down);
		decomposition(r, down);
		decomposition(p-q, down);
		res = 1.0;
		for(int ix = 0; ix != pos; ++ix){
			minimal = MIN(up[ix], down[ix]);
			up[ix] -= minimal;
			down[ix] -= minimal;
            res = res * pow(prime[ix], up[ix]);
			res = res / pow(prime[ix], down[ix]);
		}
		/*for(int ix = 0; ix != pos; ++ix)
            if(up[ix]) printf("%d^%d x ", prime[ix], up[ix]);
        printf("\ndown:\n");
        for(int ix = 0; ix != pos; ++ix)
            if(down[ix]) printf("%d %d x ", prime[ix], down[ix]);*/
		printf("%.5f\n", res);
	}
	return 0;
}
