#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

int main(){
	int K, N, curr;
	scanf("%d", &K);
	vector<int> seq;
	seq.reserve(1000);
	bool flah;
	while(K--){
		scanf("%d", &N);
		for(int ix = 0; ix != N; ++ix){
			scanf("%d", &curr);
			seq.push_back(curr);
		}
		bool flag = true;
		for(int ix = 0; ix != N; ++ix){
			for(int jx = 0; jx < ix; ++jx)
				if(seq[ix] == seq[jx] ||
				   abs(ix - jx) == abs(seq[ix] - seq[jx])){
					flag = false;
					break;
				}
		}
		if(flag) printf("YES\n");
		else printf("NO\n");
		seq.clear();
	}
	return 0;
}
