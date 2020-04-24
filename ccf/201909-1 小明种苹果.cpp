#include <cstdio>
#include <cstring>

int num[1001];

int main(){
	int N, M, total = 0, curr;
	scanf("%d %d", &N, &M);
	memset(num, 0, sizeof(num));
	for(int ix = 0; ix != N; ++ix){
		scanf("%d", &curr);
		total += curr;
		for(int jx = 0; jx != M; ++jx){
			scanf("%d", &curr);
			num[ix] -= curr;
		}
		total -= num[ix];
	}
	int maxpos = 0;
	for(int ix = 1; ix != N; ++ix)
		if(num[ix] > num[maxpos])
			maxpos = ix;
	printf("%d %d %d\n", total, maxpos + 1, num[maxpos]);
	return 0;
}
