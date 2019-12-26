#include <cstdio>
int main(){
	int N, a, b;
	scanf("%d", &N);
	for(int ix = 0; ix != N; ++ix){
		scanf("%d %d", &a, &b);
		printf("%d\n", a + b);
	}
	return 0;
}
