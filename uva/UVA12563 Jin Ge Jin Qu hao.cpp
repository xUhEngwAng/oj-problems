#include <cstdio>
#include <cstring>
#define MAXN  (10000)
#define JINGE (678)

int num[MAXN], len[MAXN], arr[51];

int main(){
	int T, n, t, cnt = 1;
	scanf("%d", &T);
	for(int ix = 1; ix <= T; ++ix){
		printf("Case %d: ", ix);
		scanf("%d %d", &n, &t);
		for(int jx = 1; jx <= n; ++jx)
			scanf("%d", arr + jx);
		memset(num, 0, sizeof(num));
		memset(len, 0, sizeof(len));
		for(int jx = 1; jx <= n; ++jx){
			for(int kx = t - 1; kx > 0; --kx){
				if(kx < arr[jx]) continue;
				if(num[kx] < num[kx - arr[jx]] + 1){
					num[kx] = num[kx - arr[jx]] + 1;
					len[kx] = len[kx - arr[jx]] + arr[jx];
				}else
				if(num[kx] == num[kx - arr[jx]] + 1 && 
				   len[kx] < len[kx - arr[jx]] + arr[jx])
					len[kx] = len[kx - arr[jx]] + arr[jx];
			}
		}
		printf("%d %d\n", num[t-1] + 1, len[t-1] + JINGE);
	}
	return 0;
}
