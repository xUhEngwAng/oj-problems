#include <cstdio>
#include <cstring>
#define MAX(X, Y) ((X) > (Y)? (X): (Y))

struct entry{
	int time, value;
}info[100];

int dp[1001];

int main(){
	int T, M;
	scanf("%d %d", &T, &M);
	for(int ix = 0; ix != M; ++ix)
		scanf("%d %d", &info[ix].time, &info[ix].value);
	memset(dp, 0, sizeof(dp));
	for(int ix = 0; ix != M; ++ix)
	for(int jx = T; jx >= 0; --jx)
		if(info[ix].time <= jx)
			dp[jx] = MAX(dp[jx], dp[jx - info[ix].time] + info[ix].value);
	printf("%d\n", dp[T]);
	return 0;
}
