#include <algorithm>
#include <cstdio>
using namespace std;

#define VERSION2

/*
 * 这个题一开始有一个测试点没有过，检查了挺久，都感觉这么简单的题
 * 我的算法怎么可能有问题？后来发现原来是在 upper_bound 里面，在
 * 一个 int 的数组里面查找 long long 类型怕是有点问题。数组也改成
 * long long 就 AC 了。
 * 后来看了题解，发现
 *
 * upper_bound(arr + ix, arr + N, (long long)arr[ix] * p);
 *
 * 居然也能A？佛了，想不明白为什么。
 */

#ifdef VERSION1

int main(){
	int N, p;
	scanf("%d %d", &N, &p);
	long long *arr = new long long[N];
	for(int ix = 0; ix != N; ++ix)
		scanf("%lld", arr + ix);
	sort(arr, arr + N);
	int maxNum = 0, pos;
	long long target;
	for(int ix = 0; ix + maxNum < N; ++ix){
		target = p * arr[ix];
		pos = upper_bound(arr + ix, arr + N, target) - arr;
		if(pos - ix > maxNum)
			maxNum = pos - ix;
	}
	printf("%d\n", maxNum);
	return 0;
}

#else

//VERSION TWO: two pointers

/*
 * 双指针法的思路是从头到尾对有序序列进行一次遍历，利用序列的单调
 * 性 lo 和 hi 都只会单调增加，遍历的时间复杂度为 O(n)，相比于上
 * 面的方案性能稍微会好一点。编码过程中还产生了一些问题，一开始我
 * 是初始化 lo = 0, hi = 1, maxNum = 0，此时对于 N = 1 的情形
 * 无法给出正确的答案。应该初始化 hi = 0 或者 maxNum = 1。
 */

#define MAXINT (~(1 << 31))

int main(){
	int N, p;
	scanf("%d %d", &N, &p);
	int *arr = new int[N];
	for(int ix = 0; ix != N; ++ix)
		scanf("%d", arr + ix);
	sort(arr, arr + N);
	int maxNum = 0, lo = 0, hi = 0;    //[lo, hi)
	long long target = 0;
	while(hi < N){
		target = (long long)arr[lo] * p;
		if(target > MAXINT) hi = N;
		else
			while(hi < N && arr[hi] <= target) ++hi;
		if(maxNum < hi - lo) maxNum = hi - lo;
		++lo;
	}
	printf("%d\n", maxNum);
	return 0;
}

#endif
