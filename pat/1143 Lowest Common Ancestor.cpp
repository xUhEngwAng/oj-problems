#include <unordered_map>
#include <cstdio>
#include <algorithm>
using namespace std;

/*
 * 这个题和 1151 是姊妹题啊，几乎是一模一样的，只是数据给出
 * 方式以及时限不一样。这个题的时限是 205 ms，可以说相当苛刻。
 *
 * 我原来的方法也是非常暴力，利用得到的先序遍历，由于这是棵二
 * 叉搜索树，对先序遍历排个序就得到中序遍历，然后利用两个遍历
 * 做个递归建树，简直是拿手操作。对于每个查询仍然和 1151 一样，
 * 这里不再赘述。
 *
 * 这里首先对时间复杂度进行分析。考虑建树的过程，最坏情况下不过
 * 10,000 层递归嵌套，然而我的递归里面还有一个循环来找右子树的
 * 起始位置，因此最坏情况下是 O(N^2) 的时间复杂度。当 N=10,000
 * 时这就是 10^8 次运算，也就是 100 ms，一半的时间就没了。再考
 * 虑查询的过程，每个查询至多上溯 N 次，因此是 O(NlogN)，如果
 * N = 10, 000，一共有 1,000 个查询那就是 1.4 x 10^8 次运算，
 * 就是 140 ms，这里的估算还没有计算内存分配的开销，所以妥妥
 * 超时，还是两个测试点。
 *
 * 一开始的改进是把 map 换成了 unordered_map，仍然是两个测试
 * 点超时，让人非常绝望。后来把中序遍历序列给取消了，因为直接找
 * 先序遍历里面第一个大于根节点的节点，就是右子树的根节点。两者
 * 在时间开销上差别不大，不过不需要分配中序遍历的空间了，结果一
 * 个测试点通过了，是 188 ms。所以分配 10,000 的空间至少要 12
 * ms，也就是分配单位空间需要 1200 次普通的运算开销！我也是第
 * 一次很直观地知道分配空间有多耗时。
 *
 * 接下来我觉得我算法的主要瓶颈在于建树的过程，毕竟 O(N^2) 确
 * 实太高了。我灵机一动，既然先序遍历具有某种分布情况，即左子树
 * 的节点都小于右子树，那么我可以通过二分查找来找到第一个大于
 * 根节点的节点，也就是右子树的根节点，这可以通过一个 upper_bound
 * 来实现。这样，建树的开销就减小到了 O(NlogN)，所有测试点都通
 * 过了。
 *
 * 最后为了测试 unordered_map 和 map 的差异，我又把代码改回了
 * map 的版本，结果两个测试点都没有通过......看来前者确实还是
 * 会快一些的，在关键码冲突很小的情况下。
 */

struct node{
	int parent;
	int depth;
	node() = default;
	node(int p , int dep): parent(p), depth(dep){}
};

unordered_map<int, node> graph;

void construct(int *preorder, int N, int parent, int depth){
	if(N == 0) return;
	int curr = preorder[0];
	graph[curr] = node(parent, depth);
	int rightpos = upper_bound(preorder + 1, preorder + N, curr) - preorder;
	construct(preorder + 1, rightpos - 1, curr, depth + 1);
	construct(preorder + rightpos, N - rightpos, curr, depth + 1);
}

int main(){
	int M, N;
	scanf("%d %d", &M, &N);
	int *preorder = new int[N];
	for(int ix = 0; ix != N; ++ix){
		scanf("%d", preorder + ix);
	}
	construct(preorder, N, -1, 0);

	int one, two, anc1, anc2, dep1, dep2;
	while(M--){
		scanf("%d %d", &one, &two);
		if(graph.find(one) == graph.end()){
			if(graph.find(two) == graph.end())
				printf("ERROR: %d and %d are not found.\n", one, two);
			else
				printf("ERROR: %d is not found.\n", one);
			continue;
		}
		if(graph.find(two) == graph.end()){
			printf("ERROR: %d is not found.\n", two);
			continue;
		}
		anc1 = one, anc2 = two;
		dep1 = graph[anc1].depth;
		dep2 = graph[anc2].depth;
		while(dep1 > dep2){
			anc1 = graph[anc1].parent;
			dep1 = graph[anc1].depth;
		}
		while(dep2 > dep1){
			anc2 = graph[anc2].parent;
			dep2 = graph[anc2].depth;
		}
		if(anc1 == anc2)
			if(graph[one].depth < graph[two].depth)
				printf("%d is an ancestor of %d.\n", one, two);
			else
				printf("%d is an ancestor of %d.\n", two, one);
		else{
			while(anc1 != anc2){
				anc1 = graph[anc1].parent;
				anc2 = graph[anc2].parent;
			}
			printf("LCA of %d and %d is %d.\n", one, two, anc1);
		}
	}
	return 0;
}
