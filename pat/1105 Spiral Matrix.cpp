#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int main(){
	int N;
	scanf("%d", &N);
	int *arr = new int[N];
	for(int ix = 0; ix != N; ++ix)
		scanf("%d", arr + ix);
	sort(arr, arr + N);
	int n, m, tmp;
	for(int ix = 1;; ++ix){
		tmp = N / ix;
		if(tmp < ix) break;
		if(ix * tmp == N){
			m = tmp;
			n = ix;
		}
	}

	vector<vector<int>> res(m, vector<int>(n, 0));
	int begin = 0, count = N - 1;
	while(n > 0){
		for(int ix = 0; ix != n; ++ix)
			res[begin][begin + ix] = arr[count--];
		for(int ix = 1; ix != m; ++ix)
			res[begin + ix][begin + n - 1] = arr[count--];
		for(int ix = n - 2; ix >= 0; --ix)
			res[begin + m - 1][begin + ix] = arr[count--];
		if(n != 1)
			for(int ix = m - 2; ix >= 1; --ix)
				res[begin + ix][begin] = arr[count--];
		m -= 2;
		n -= 2;
		begin++;
	}
	for(auto v: res){
		printf("%d", v[0]);
		for(int ix = 1; ix != v.size(); ++ix)
			printf(" %d", v[ix]);
		printf("\n");
	}
	return 0;
}
