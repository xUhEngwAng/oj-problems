#include <bitset>
#include <cstdio>
using namespace std;

/*
 * 这个题一开始我是用 set 做的，结果第二个测试点超时了，于是
 * 我就把底层结构改成了 bitset，结果第二个测试点还是超时！我
 * 就傻了，怎么想我这个代码也不可能超时啊，严格的 O(M + N)
 * 的时间复杂度，超级完美！
 *
 * 于是我发现原来是边界点出现了问题，即如果派对上没有单身狗，
 * 我最后的枚举所有单身狗的循环就是死循环了，改了这个问题就
 * 通过了，所以原来第二个测试点并不是大数据点......
 */

int couples[100000];
bitset<100000> res;

int main(){
	int N, one, two;
	scanf("%d", &N);
	for(int ix = 0; ix != 100000; ++ix)
        couples[ix] = -1;
	for(int ix = 0; ix != N; ++ix){
		scanf("%d %d", &one, &two);
		couples[one] = two;
		couples[two] = one;
	}
	int M, query, couple;
	scanf("%d", &M);
	for(int ix = 0; ix != M; ++ix){
		scanf("%d", &query);
		couple = couples[query];
		if(couple != -1 && res[couple])
            res[couple] = false;
        else
            res[query] = true;
	}
	printf("%d\n", res.count());
	if(res.count() == 0) return 0;

	int pos = 0;
	while(!res[pos]) ++pos;
    printf("%05d", pos);
    for(pos++; pos <= 100000; ++pos)
        if(res[pos]) printf(" %05d", pos);
	return 0;
}
