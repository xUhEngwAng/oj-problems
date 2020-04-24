#include <cstdio>
#include <algorithm>
using namespace std;

int arr[100000];

int main(){
	int n;
	scanf("%d", &n);
	for(int ix = 0; ix != n; ++ix)
		scanf("%d", arr + ix);
	int min, max, sum;
	double mid;
	min = arr[0], max = arr[n - 1];
	if(min > max) swap(min, max);
	printf("%d ", max);
	if(n & 1) printf("%d ", arr[n>>1]);
	else{
		sum = arr[n >> 1] + arr[(n >> 1) - 1];
		//printf("sum: %d\n", sum);
		if(sum & 1){
			mid = (double)sum / 2;
			printf("%.1f ", mid);
		}
		else printf("%d ", sum >> 1);
	}
	printf("%d\n", min);
	return 0;
}
