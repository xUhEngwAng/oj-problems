#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;

/*
 * 这个题还花了我挺久时间的。首先不得不说 PAT 确实垃圾，这个题
 * 的题意一开始就有问题，设散列表的长度为 m，它定义的失败查找
 * 长度最大为 m + 1，而实际上 ceil(m / 2) 次比对就可以确定失
 * 查找。
 *
 * 然后说说我的问题，首先一个问题是要求输出的字符串我忘了加 .
 * 导致一开始一堆测试点错误......这种细节问题需要注意。
 *
 * 另一个问题则更加细节，一般说来，由于 m 是质数，那么 m 都是
 * 奇数，所以 ceil(m / 2) = (m + 1) / 2，平方探测法只需要探
 * 测到 m / 2 = ceil(m / 2) - 1 就可以终止了，后续的探测必然
 * 与此前的探测位置重复。然而我忽略了 m = 2 的情形，此时
 *
 * m / 2 != ceil(m / 2) - 1
 *
 * jx = ceil(m / 2) 是值得尝试的位置。
 */

bool isPrime(int m){
	if(m == 1) return false;
	for(int ix = 2; ix <= sqrt(m) + 0.5; ++ix)
		if(m % ix == 0) return false;
	return true;
}

int main(){
	int msize, N, M;
	scanf("%d %d %d", &msize, &N, &M);
	while(!isPrime(msize)) msize++;
	vector<int> hash(msize, 0);
	int probcnt = (msize + 1) / 2, pos, curr;
	for(int ix = 0, jx; ix != N; ++ix){
		scanf("%d", &curr);
		for(jx = 0; jx <= probcnt; ++jx){
			pos = (curr + jx * jx) % msize;
			if(hash[pos] == 0){
				hash[pos] = curr;
				break;
			}
		}
		if(jx == probcnt + 1)
			printf("%d cannot be inserted.\n", curr);
	}

	int count = 0;
	for(int ix = 0, jx; ix != M; ++ix){
		scanf("%d", &curr);
		for(jx = 0; jx <= probcnt; ++jx){
			pos = (curr + jx * jx) % msize;
			if(hash[pos] == 0 || hash[pos] == curr){
				count += jx + 1;
				break;
			}
		}
		if(jx == probcnt + 1)
			count += msize + 1;
	}
	printf("%.1f\n", (double)count / M);
	return 0;
}
