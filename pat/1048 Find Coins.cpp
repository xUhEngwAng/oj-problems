#include <vector>
#include <cstdio>
using namespace std;

int main(){
	vector<int> count(501, 0);
	int N, M, curr;
	scanf("%d %d", &N, &M);
	for(int ix = 0; ix != N; ++ix){
		scanf("%d", &curr);
		count[curr]++;
	}

	int ix;
	for(ix = 0; ix != 501; ++ix){
		if(count[ix] == 0) continue;
		curr = M - ix;
		if(curr > 500 || curr <= 0) continue;
		count[ix]--;
		if(count[curr] > 0){
			printf("%d %d\n", ix, curr);
			break;
		}
		count[ix]++;
	}
	if(ix == 501) printf("No Solution\n");
	return 0;
}
