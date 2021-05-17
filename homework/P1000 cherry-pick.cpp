#include <stdio.h>
#include <vector>
#include <algorithm>

int main()
{
    freopen("1.out", "w", stdout);
    int M, N, K, L, R;
	std::vector<int> A, tmp, res;
	scanf("%d", &N);
	A.resize(N);
	tmp.reserve(N);
	for(int ix = 0; ix != N; ++ix)
		scanf("%d", &A[ix]);
	scanf("%d", &M);
	for(int ix = 0; ix != M; ++ix){
		scanf("%d %d %d", &K, &L, &R);
		tmp.assign(A.begin()+L-1, A.begin()+R);
		sort(tmp.begin(), tmp.end());
		res.clear();
        for(int jx = K-1; jx < tmp.size(); jx += K){
			res.push_back(tmp[jx]);
		}
		if(res.empty()) printf("EMPTY\n");
		else{
			printf("%d", res[0]);
			for(int jx = 1; jx < res.size(); ++jx)
				printf(" %d", res[jx]);
			printf("\n");
		}
	}
	return 0;
}
