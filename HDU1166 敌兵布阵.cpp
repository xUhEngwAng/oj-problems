#include <cstdio>
#include <cstring>

int num[50001], sum[50001];
int T, N;

int low_bit(int x){
	return x & (-x);
}
void update(int pos, int value){
	while(pos <= N){
		sum[pos] += value;
		pos += low_bit(pos);
	}
}
int get_sum(int pos){
	int ret = 0;
	while(pos > 0){
		ret += sum[pos];
		pos -= low_bit(pos);
	}
	return ret;
}

int main(){
	int one, two, res;
	char cmd[6];
	scanf("%d", &T);
	for(int ix = 1; ix <= T; ++ix){
		printf("Case %d:\n", ix);
		scanf("%d", &N);
		memset(sum, 0, sizeof(int) * (N + 1));
		for(int jx = 1; jx <= N; ++jx){
			scanf("%d", num + jx);
			update(jx, num[jx]);
		}
		while(true){
			scanf("%s", cmd);
			if(cmd[0] == 'E') break;
            scanf("%d %d", &one, &two);
			if(cmd[0] == 'A') update(one, two);
			else if(cmd[0] == 'S') update(one, -two);
			else{
				res = get_sum(two) - get_sum(one-1);
				printf("%d\n", res);
			}
		}
	}
	return 0;
}
