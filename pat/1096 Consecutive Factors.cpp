#include <cstdio>
#include <cmath>

/*
 * 这个题我一开始的问题是题意理解错了，我以为是所有因数中
 * 的最长连续因数，比如说 36 的因数有 2,3,4,6，所以应该
 * 输出 2*3*4。
 * 
 * 后来发现并不是这样，正确的做法是首先将 N 进行因数分解，
 * 选择因数分解中最长的连续因数。这样，36可以写作
 * 
 * 36 = 2 * 2 * 3 * 3
 *
 * 所以应该输出 2*3。为了解决这个问题，我直接写了一个蛮力
 * 穷举的算法，即逐个枚举开始于 ix = 2, 3, ... 的最长连续
 * 因数，没想到通过了？？？400ms的限时还只用了3ms，PAT 的
 * 数据好菜啊。
 */

int main(){
	int N;
	scanf("%d", &N);
	int max = 0, count, begin, end = sqrt(N);
	long long product;
	for(int ix = 2; ix <= end; ++ix){
        count = 0;
        product = 1;
        for(int jx = ix; ; ++jx){
            product *= jx;
            if(N % product != 0) break;
            ++count;
        }
        if(count > max){
            max = count;
            begin = ix;
        }
        if(product >= N) break;
	}
	if(max == 0){
        max = 1;
        begin = N;
	}
	printf("%d", max);
	printf("\n%d", begin);
	for(int ix = 1; ix < max; ++ix){
		printf("*%d", begin + ix);
	}
	printf("\n");
	return 0;
}
