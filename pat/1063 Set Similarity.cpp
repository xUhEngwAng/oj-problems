#include <cstdio>
#include <set>
#include <vector>
using namespace std;

/*
 * 这种 stl 题感觉都挺容易超时的。我一开始的思路是：
 *
 * 为了计算两个集合的交集以及并集的元素数量，首先引入一个新的
 * 集合 s，令 s = data[one]；随后逐个将第二个集合中的元素插
 * 到 s 中，如果元素已经存在，则 ++common。插入结束后，集合s
 * 的大小就是 total。很不幸，这种方法超时了。
 *
 * 我的解决方案是，开了一个二维数组，存储已经计算出结果的query，
 * 如果后续出现相同的 query，则可以直接查表得到答案。这样处理后
 * 就通过了，最大的测试集大约需要370ms。
 *
 * 后来看《算法笔记》的题解，发现和我的第一种方法没什么不同，只不
 * 过求交集和并集的元素数量时，只是对第二个集合做遍历，判断其中
 * 的元素是否在第一个集合中出现过。我这样一改，也没有用打表，居然
 * 只需要180ms的时间！我承认这种方法是比我的好，但是应该不至于有
 * 这么大的差别吧！我的方案时间复杂度是 O((m + n)log(m + n))，
 * 该方案时间复杂度是 O(mlogn)，在 m, n 都很大时区别不大吧？！
 * 也就两倍的差距啊，不过也应该看到，在这种时候两倍的差距影响还是
 * 很大的。后来还加了打表，又快了一点点，只需要140ms了。
 *
 * 我水平果然不够啊。
 */

int main(){
	int nsets, size, curr;
	scanf("%d", &nsets);
	vector<set<int>> data(nsets);
	for(int ix = 0; ix != nsets; ++ix){
		scanf("%d", &size);
		while(size--){
			scanf("%d", &curr);
			data[ix].insert(curr);
		}
	}

	int k, one, two, common, total;
	float res, saved[50][50];
	for(int ix = 0; ix != 50; ++ix)
		for(int jx = 0; jx != 50; ++jx)
			saved[ix][jx] = 0;
	scanf("%d", &k);
	while(k--){
		scanf("%d %d", &one, &two);
		one -= 1, two -= 1;
		if(saved[one][two] != 0){
			printf("%.1f%\n", saved[one][two]);
			continue;
		}
		common = 0, total = data[one].size();
		for(int e : data[two]){
			if(data[one].find(e) != data[one].end()) ++common;
			else ++total;
		}
		res = 100 * ((float)common / total);
		saved[one][two] = res;
		printf("%.1f%\n", res);
	}
	return 0;
}
