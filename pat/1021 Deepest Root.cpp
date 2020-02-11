#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * 这个题相当有意思啊，我第一次是写的超级蛮力算法，即对所有节点
 * 都做一次 dfs，就这样都没有超时，一次提交就 AC 了。然而我看到
 * 其他人的提交，有的运行时间是我的百分之一？！于是就深入探索了
 * 一下，发现这个题有深刻的内涵啊，又研究了好久。
 *
 * 最优的算法如下：
 *
 * 1. 以图中任一节点为根节点，进行一次 dfs，同时记录所有深度最深
 *    的节点，记作集合 A。
 * 2. 任取集合 A 中的一个节点为根节点，再进行一次 dfs，同样记录
 *    所有深度最深的节点，记作集合 B。
 * 3. A，B的并集即为要求的 deepest root。
 *
 * 这个算法正确性的证明是比较复杂的，主要是关注三个要点，即
 *
 * 1. 集合 A 的所有节点一定是 deepest root的证明。
 * 2. 任意两条最长路径一定是相交的证明。
 * 3. 所有的最长路径一定至少相交于一点的证明。
 *
 * 这样，最长路径之间大约可以形成下面的形式：
 *
 *      A1   --- \             / --- A1'
 *      A2   ---    O ------O'   --- A2'
 *      ...  --- /             \ --- ...
 *      Ak   ---                 --- Ak'
 *
 * 其中，Ak 可以与 Ak' 任意组合形成不同的最长路径。以图中任一节点
 * 为根首先进行一次 dfs，记录的集合 A 要么 是 A1, A2, ..., Ak 
 * 的集合，要么是 A1', A2', ..., Ak' 的集合，要么是两者的并集。
 * 再以集合 A 中任一节点为根进行一次 dfs，得到的集合 B 必然是最长
 * 路径的另一边节点的集合。
 */

vector<vector<int>> tree;
vector<bool> visited;
vector<int> res, candidates;
int maxDepth;

void dfs(int root, int depth){
	visited[root] = true;
	if(depth > maxDepth){
		maxDepth = depth;
		candidates.clear();
		candidates.push_back(root);
	}
	if(depth == maxDepth)
		candidates.push_back(root);
	for(int e : tree[root])
		if(!visited[e])
			dfs(e, depth + 1);
}


int main(){
	int N, one, two;
	scanf("%d", &N);
	tree = vector<vector<int>>(N + 1);
	visited = vector<bool>(N + 1, false);
	for(int ix = 1; ix != N; ++ix){
		scanf("%d %d", &one, &two);
		tree[one].push_back(two);
		tree[two].push_back(one);
	}

	int curr, K = 1, dep, size;
	dfs(1, 0);
	for(int ix = 1; ix <= N; ++ix)
		if(!visited[ix]){
			++K;
			dfs(ix, 0);
		}
	if(K != 1){
		printf("Error: %d components\n", K);
		return 0;
	}

	for(int ix = 1; ix <= N; ++ix)
		visited[ix] = false;
	res.assign(candidates.begin(), candidates.end());
	candidates.clear();
	dfs(res[0], 0);
	res.insert(res.end(), candidates.begin(), candidates.end());
	sort(res.begin(), res.end());
	auto endit = unique(res.begin(), res.end());

	for(auto it = res.begin(); it != endit; ++it)
		printf("%d\n", *it);
	return 0;
}
