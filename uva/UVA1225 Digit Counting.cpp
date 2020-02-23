#include <vector>
#include <string>
#include <cstdio>
using namespace std;

vector<vector<int>> cnt(10000, vector<int>(10));

int main(){
	int N, curr;
	scanf("%d", &N);

	string str;
	for(int ix = 1; ix != 10000; ++ix){
		str = to_string(ix);
		cnt[ix].assign(cnt[ix - 1].begin(), cnt[ix - 1].end());
		for(char ch : str)
			cnt[ix][ch - '0']++;
	}
	while(N--){
		scanf("%d", &curr);
		printf("%d", cnt[curr][0]);
		for(int ix = 1; ix != 10; ++ix)
			printf(" %d", cnt[curr][ix]);
		printf("\n");
	}
	return 0;
}
