//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
using namespace std;
int main(){
	int m, n, max = 0;
	scanf("%d %d", &n, &m);
	int* raw_data = new int[n];
	for(int i = 0; i != n; i++){
		scanf("%d", &raw_data[i]);
		if (raw_data[i] > max) max = raw_data[i];
	}
	
	bool* bit_map = new bool[max + 1];
	int* accu = new int[max + 1];
	for (int ix = 0; ix != max + 1; ++ix)
		bit_map[ix] = 0;
	for (int ix = 0; ix != n; ++ix)
		bit_map[raw_data[ix]] = 1;
	accu[0] = bit_map[0];
	for (int ix = 1; ix != max + 1; ++ix)
		accu[ix] = accu[ix - 1] + bit_map[ix];

	for(int ix = 0, a, b; ix != m; ++ix){
		scanf("%d %d", &a, &b);
		if (a > max){
			printf("0\n");
			continue;
		}
		if (b > max) b = max;
		printf("%d\n", accu[b] - accu[a] + bit_map[a]);
	}
	//while(getchar() != ' ');
	return 0;
}
