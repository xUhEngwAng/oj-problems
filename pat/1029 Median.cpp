#include <cstdio>
#include <vector>
using namespace std;

/*
 * 这个题一开始我都是拒绝做的，应该最优的算法确实太复杂了，有
 * 各种细节的处理，时间复杂度是 O(log(min(m, n)))。但是 PAT
 * 的题一如既往的数据很差，本题就算写一个 O(m + n) 的算法也
 * 不会超时，所以我就......
 *
 * 有机会我回来写写最优解。
 */

int main(){
	int m, n;
	vector<int> arr1, arr2;
	scanf("%d", &m);
	arr1.resize(m);
	for(int ix = 0; ix != m; ++ix)
		scanf("%d", &arr1[ix]);
	scanf("%d", &n);
	arr2.resize(n);
	for(int ix = 0; ix != n; ++ix)
		scanf("%d", &arr2[ix]);
	int count = 0, mid = (m + n  + 1) >> 1, res;
	for(int ix = 0, jx = 0; ix != m || jx != n;){
		if(jx == n || (ix < m && arr1[ix] < arr2[jx])){
			if(++count == mid){
				res = arr1[ix];
				break;
			}
            ++ix;
		}
		else{
			if(++count == mid){
				res = arr2[jx];
				break;
			}
            ++jx;
		}
	}
	printf("%d\n", res);
	return 0;
}
