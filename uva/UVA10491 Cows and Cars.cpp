#include <cstdio>

int main(){
	int n_cow, n_car, n_show, n;
	double res;
	while(scanf("%d %d %d", &n_cow, &n_car, &n_show) == 3){
		n = n_cow + n_car;
		res =  n_car * n_cow;
		res += (n_car - 1) * n_car;
		res = res / (n * (n - 1 - n_show));
		printf("%.5f\n", res);
	}
	return 0;
}
