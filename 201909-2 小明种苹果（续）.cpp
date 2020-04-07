#include <cstdio>
#include <cstring>

bool drop[1001];

int main(){
	int N, M, total = 0, curr, tmp;
	scanf("%d", &N);
	memset(drop, 0, sizeof(drop));
	for(int ix = 0; ix != N; ++ix){
		scanf("%d %d", &M, &curr);
		while(--M){
			scanf("%d", &tmp);
			if(tmp <= 0) curr += tmp;
			else
			if(curr != tmp){
				drop[ix] = true;
				curr = tmp;
			}
		}
		total += curr;
	}
	int cnt = 0, group = 0;
	for(int ix = 0; ix != N; ++ix)
		if(drop[ix]) ++cnt;
	for(int ix = 0; ix != N; ++ix){
		if(drop[ix] && drop[(ix + 1) % N] && drop[(ix + 2) % N])
			++group;
	}
	printf("%d %d %d\n", total, cnt, group);
	return 0;
}
