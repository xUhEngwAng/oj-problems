#include <unordered_map>
#include <cstdio>
using namespace std;

/*
 * 这个题我本来用的蛮力算法，就是首先根据先序和中序遍历构造出
 * 原来的二叉树，用的是父节点表示法。随后再逐个针对每个 query
 * 进行查询，简单说来就是不断上溯，直到找到两者的公共祖先节点。
 * 蛮力算法大约花了 968 ms，时限是 1000ms，还是挺极限的。
 *
 * 后来我针对我的查询过程做了一些修改，查询过程首先对深度更深
 * 的节点进行上溯，直到两者的深度相同，因此每次更新后都要比较
 * 两者的深度。我本来写的是
 *
 * while(graph[anc1].depth > graph[anc2].depth)
 *     anc1 = graph[anc1].parent;
 * while(graph[anc2].depth > graph[anc1].depth)
 *     anc2 = graph[anc2].parent;
 *
 * 这样访问两个节点都需要 O(logN) 的时间。可是其中一个节点的
 * 深度是不变的，因此引入了一个变量来表示其深度，就可以节约一
 * 半的循环时间。时间开销也降到了 732 ms。
 *
 * 可是我觉得还是太慢，继续想着怎么优化。正好这几天学了学
 * unordered_map，就把用到的 map 换成了 unordered_map，这个
 * 首要的好处是其他部分都不用修改就可以直接用。结果耗时直接降到
 * 了 205 ms！我也算是比较满意了。
 *
 * 需要说明的是，unordered_map 底层是用 hash 来实现的，冲突解
 * 决方案是独立链法，理论上查询和访问的时间复杂度是 O(1)，如果
 * N = 10, 000 的话，大约快了 O(logN) = 14倍，实际上只快了两倍。
 * 一方面是代码还存在其他开销，比如内存分配，建树这种，就不是只有
 * 查询；另一方面，默认的 hash function 是模余法，模余运算虽然
 * 号称是 O(1) 的运算，实际开销却非常大，在发生冲突是还要沿着链
 * 逐个查找，因此相对于 map 其实也不是那么美好。
 */

struct node{
	int parent;
	int depth;
	node() = default;
	node(int p , int dep): parent(p), depth(dep){}
};

unordered_map<int, node> graph;

void construct(int *preorder, int *inorder,
	           int N, int parent, int depth){
	if(N == 0) return;
	int curr = preorder[0];
	graph[curr] = node(parent, depth);
	int leftcnt = 0;
	while(inorder[leftcnt] != curr) ++leftcnt;
	construct(preorder + 1, inorder, leftcnt, curr, depth + 1);
	construct(preorder + leftcnt + 1, inorder + leftcnt + 1,
		      N - leftcnt - 1, curr, depth + 1);
}

int main(){
	int M, N;
	scanf("%d %d", &M, &N);
	int *preorder = new int[N];
	int *inorder  = new int[N];
	for(int ix = 0; ix != N; ++ix)
		scanf("%d", inorder + ix);
	for(int ix = 0; ix != N; ++ix)
		scanf("%d", preorder + ix);
	construct(preorder, inorder, N, -1, 0);
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
