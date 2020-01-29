#include <cstdio>
#include <cmath>

/*
 * PAT 真的是垃圾，数据太野鸡了！
 *
 * 这个题我第一次提交有一个测试点没过，然后我检查了一下，马上
 * 发现我只找了 sqrt(N) 以内的质数，而 N 是可能有大于 sqrt(N)
 * 的质因子的，比如 N = 2 * (N >> 1)。
 *
 * 于是我把代码改成找 N / 2 以内的全部质数，但是这样 N 稍微
 * 大一点就会超时很多很多。然后我发现我的埃氏筛实现有问题！对于
 * 已经判断不是素数的数字，我仍然试图筛掉它们的倍数，可是这些数
 * 早就被此前的质因子给筛掉了啊！改进之后快了不少，但还是超时。
 * 
 * 最后终于想出来一种神仙解法，我还是只找 sqrt(N) 以内的质数，
 * 如果 N 有 大于 sqrt(N) 的质因子，那么就只有一个，所以最后
 * 单独对除以了所有质因子的 N 进行判别，如果 N 大于 1，那么剩下
 * 的 N 就是那个大于 sqrt(N) 的质因子！
 *
 * 至此，我觉得我已经完美地解决了问题，太优雅了，每一步都是最优
 * 解。于是我兴冲冲地把新版本的代码拿去提交，『答案错误』，仍然是
 * 开始的测试点没有通过。我佛了。
 *
 * 最后我找了很久很久错误，把我能想到所有边界情况都测试了，结果
 * 都是正确的。我终于笃定我的代码是没有问题的，那么就只有一种可能
 * 性： N = 1。可是我不敢相信，1 怎么能做质因子分解？不管怎么样，
 * 我还是为这种情况单独写了一个判断语句。提交，『答案正确』。
 * 我又佛了。
 *
 * 我把一开始错误的代码找到，也为它添加了 N = 1 的判断，再提交。
 * 『答案正确』。我：？？？PAT 真的是垃圾，数据太野鸡了！
 */

int main(){
	int N;
	scanf("%d", &N);
	if(N == 1){
        printf("1=1\n");
        return 0;
    }
	int len = 1 + sqrt(N);
	int end = sqrt(len);
	int pow;
	bool *noprimes = new bool[len];
	for(int ix = 2; ix <= end; ++ix){
        if(noprimes[ix] == true)
            continue;
		pow = ix * ix;
		while(pow < len){
			noprimes[pow] = true;
			pow += ix;
		}
	}
	int *primes = new int[len];
	int count = 0;
	for(int ix = 2; ix < len; ++ix)
		if(!noprimes[ix]) primes[count++] = ix;

	int k, tmp = N;
	printf("%d=", N);
	bool flag = true;
	for(int ix = 0; ix < count && tmp != 1; ++ix){
		k = 0;
		while(tmp % primes[ix] == 0){
            tmp = tmp / primes[ix];
			++k;
		}
        if(k != 0){
            if(flag) flag = false;
            else printf("*");
            printf("%d", primes[ix]);
            if(k != 1) printf("^%d", k);
        }
	}
	if(tmp != 1){
        if(!flag) printf("*");
        printf("%d", tmp);
	}
	printf("\n");
	return 0;
}
