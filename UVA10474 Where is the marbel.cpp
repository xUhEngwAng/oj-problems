#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * 查看了《算法竞赛入门经典》中给出的题解，发现自己代码存在的一些问题：
 * 1. 使用了vector.resize()每次动态调整大小，这样会引入额外的开销。
 *    最好的方法是直接就指定vector的大小为最大值10000。
 * 2. 使用find函数查找目标，但是该函数是逐个查找目标元素啊，时间复杂
 *    度是O(n)。题解中是使用lower_bound函数，我不会用。
 * 3. 题解使用scanf的返回值确定终止条件，我也不会用，虽然没有影响。
 * 4. 题解是基于数组来实现的，数组的sort以及lower_bound等的参数是我
 *    不熟悉的。
 * 综上，我这个垃圾代码居然也可以ac，只能说明这个题的数据不行。
 */

int main(){
	int N, Q, query, count = 1;
	vector<int>::iterator pos;
	vector<int> marbles;
	while(true){
		scanf("%d %d", &N, &Q);
		if(N == 0 && Q == 0) break;
		marbles.resize(N);
		for(int ix = 0; ix != N; ++ix)
			scanf("%d", &marbles[ix]);
		sort(marbles.begin(), marbles.end());
		printf("CASE# %d:\n", count);
		for(int ix = 0; ix != Q; ++ix){
			scanf("%d", &query);
			pos = find(marbles.begin(), marbles.end(), query);
			if(pos == marbles.end()) printf("%d not found\n", query);
			else printf("%d found at %d\n", query, pos - marbles.begin() + 1);
		}
		++count;
	}
	return 0;
}
