#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct entry{
	int voltage, cost_src, cost_lamp, num_lamp;
}arr[1000];

int dp[1001], sum[1001];

bool cmp(const entry &one, const entry &two){
	return one.voltage < two.voltage;
}

int main(){
	//freopen("1.out", "w", stdout);
	int n, curr_cost, min_cost, min_pos;
	while(scanf("%d", &n) == 1){
		if(n == 0) break;
		for(int ix = 0; ix != n; ++ix)
			scanf("%d %d %d %d", &arr[ix].voltage, &arr[ix].cost_src, 
				                 &arr[ix].cost_lamp, &arr[ix].num_lamp);
		sort(arr, arr + n, cmp);
		sum[0] = arr[0].num_lamp;
		for(int ix = 1; ix != n; ++ix)
			sum[ix] = sum[ix-1] + arr[ix].num_lamp;

		for(int ix = 0; ix != n; ++ix){
			curr_cost = min_cost = sum[ix] * arr[ix].cost_lamp + arr[ix].cost_src;
			for(int jx = 1; jx <= ix; ++jx){
				curr_cost = dp[jx-1] + (sum[ix] - sum[jx-1]) * arr[ix].cost_lamp + arr[ix].cost_src;
				if(curr_cost < min_cost) min_cost = curr_cost;
			}
			dp[ix] = min_cost;
		}
		printf("%d\n", dp[n - 1]);
	}
	return 0;
}
