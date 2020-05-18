#include <cstdio>

int main(){
	int n, D, cnt = 1, len, p, v, l;
	double time;
	while(scanf("%d %d", &n, &D) == 2){
		if(n == 0 && D == 0) break;
		printf("Case %d: ", cnt++);
		time = 0.0;
		len = 0;
		for(int ix = 0; ix != n; ++ix){
			scanf("%d %d %d", &p, &l, &v);
			len += l;
			time += (double)l * 2 / v;
		}
		time += D - len;
		printf("%.3f\n", time);
		printf("\n");
	}
	return 0;
}
