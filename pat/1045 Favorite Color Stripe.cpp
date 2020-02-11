#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * 这个题相当有内涵啊，我这里是写了三个版本的代码，三者都是从
 * LIS 的思路出发求解的，题中给出的 Eva 最喜欢的序列相当于定义
 * 了元素之间新的顺序关系。下面逐个进行说明。
 *
 * VERSION 1 这个代码是有问题的。这个算法是通过一个 max 变量来
 * 记录当前的最长递增序列的长度，同时引入一个向量 seq，来记录这
 * 样一个序列，它最有可能与后续输入形成更长的序列。seq 更新规则
 * 是，对于当前输入 curr，首先 pop seq 中 大于 curr 的元素，
 * 然后再 push(curr)。这个思路是错误的，考虑下面一组数据
 *
 * 1 10 11 2 12
 *
 * 最长递增序列长度为 4，而使用上述算法只能得到 3。然而 PAT 数据
 * 是在垃圾，这个版本的代码是可以 AC 的，并且时间还相当短，因为
 * 复杂度为 O(n)。
 *
 * VERSION 2 是最简单的 dp 的思路，引入一个向量 count，其中
 * count[ix] 记录的是 以 arr[ix] 为最后一个元素的 LIS 的长度。
 * 容易看出，count[ix] 的更新规则是，遍历所有的 count[jx](jx < ix)
 *
 * if arr[ix] >= arr[jx]:
 *     count[ix] = MAX(count[ix], count[jx] + 1);
 *
 * 该算法的时间复杂度为 O(n^2)。
 *
 * VERSION 3 是比较巧妙的 dp 思路，其中也是引入一个向量 count，
 * 不过 count[ix] 表示长度为 ix 的 LIS 的最后一个元素的值，容易
 * 证明，count[ix] 是一个递增的序列。 count[ix] 的更新规则是，
 * 对于当前元素 curr，找到 count[ix] 中第一个大于 curr 的元素，
 * 即 it = upper_bound(count.begin(), count.end(), curr)
 *
 * 随后令 *it = curr 即可。需要注意如果 it == count.end()，则为
 * count 新增一个新的元素 curr。
 *
 * 由于查找的过程可以使用二分查找，该算法的时间复杂度为 O(nlogn)。
 *
 * 除了 LIS 的思路以外，此题还可以使用 LCS 来求解。不过此题显然与
 * 传统的 LCS 不相同，而是元素可以重复出现的 LCS，因此 LCS 中用
 * 到的二维数组 dp 的更新规则为：
 *
 * if one[i] == two[j]:
 *     dp[i][j] = MAX(dp[i-1][j], dp[i][j-1]) + 1
 * else:
 *     dp[i][j] = MAX(dp[i-1][j], dp[i][j-1])
 *
 * 该算法的时间复杂度为 O(n^2)，这里不再赘述。
 */

// VERSION 1

int _main(){
	int N, M, curr, L;
	scanf("%d", &N);
	vector<int> order(N + 1, -1);
	scanf("%d", &M);
	for(int ix = 0; ix != M; ++ix){
		scanf("%d", &curr);
		order[curr] = ix;
	}
	scanf("%d", &L);
	int max = 0;
	vector<int> seq;
	for(int ix = 0; ix != L; ++ix){
		scanf("%d", &curr);
		if(order[curr] == -1) continue;
		while(!seq.empty() && order[seq.back()] > order[curr])
			seq.pop_back();
		seq.push_back(curr);
		if(seq.size() > max) max = seq.size();
	}
	printf("%d\n", max);
	return 0;
}

//VERSION2

int __main(){
	int N, M, curr, L, max;
	scanf("%d", &N);
	vector<int> order(N + 1, -1);
	scanf("%d", &M);
	for(int ix = 0; ix != M; ++ix){
		scanf("%d", &curr);
		order[curr] = ix;
	}
	scanf("%d", &L);
	vector<int> count(L), origin(L);
	max = 0;
	int idx = 0;
	while(L--){
		scanf("%d", &curr);
		if(order[curr] == -1) continue;
		origin[idx] = curr;
		count[idx] = 1;
		for(int jx = 0; jx < idx; ++jx){
			if((order[origin[jx]] <= order[curr]) && (count[idx] < count[jx] + 1))
				count[idx] = count[jx] + 1;
		}
		if(count[idx] > max) max = count[idx];
		++idx;
	}
	printf("%d\n", max);
	return 0;
}

//VERSION3

vector<int> order;

bool cmp(int one, int two){
	return order[one] < order[two];
}

int main(){
	int N, M, curr, L, max;
	scanf("%d", &N);
	order = vector<int>(N + 1, -1);
	scanf("%d", &M);
	for(int ix = 0; ix != M; ++ix){
		scanf("%d", &curr);
		order[curr] = ix;
	}
	scanf("%d", &L);
	vector<int> count;
	vector<int>::iterator it;
	count.reserve(L);
	while(L--){
		scanf("%d", &curr);
		if(order[curr] == -1) continue;
		it = upper_bound(count.begin(), count.end(), curr, cmp);
		if(it == count.end()) count.push_back(curr);
		else *it = curr;
	}
	printf("%d\n", count.size());
	return 0;
}
