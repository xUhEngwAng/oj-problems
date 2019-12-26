//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	int *input  = new int[n];
	int *output = new int[n];
	int pr2input = -1, pr2output = 0, nr = 0, ix;
	for (int ix = 0; ix != n; ++ix)
		scanf("%d", &output[ix]);
	bool *operation = new bool[2 * n];					//0 for push, 1 for pop
	for(ix = 1; ix <= n; ++ix){
		input[++pr2input] = ix;
		operation[nr++] = 0;							//push
		if (pr2input == m) break;						//stack overflow
		while(pr2input > -1 && pr2output < n && input[pr2input] == output[pr2output]){	//pop
			pr2output++;
			pr2input--;
			operation[nr++] = 1;
		}
	}
	if (ix == n + 1 && pr2input == -1){
		for (int ix = 0; ix != 2 * n; ++ix) {
			if (operation[ix])	printf("pop\n");
			else				printf("push\n");
		}
	}
	else printf("No\n");
	//while (getchar() != ' ');
	return 0;
}
