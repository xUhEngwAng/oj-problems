#include <map>
#include <set>
#include <queue>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

/*
 * 这个题看起来容易，实现起来还是有很多细节问题需要注意。
 * 比如关于底层数据结构的选择之类的问题，搞得我还挺头疼。
 * 这里遇到了一个问题，是 dfs 和 bfs 两者对 visited 数
 * 组的更新位置。我一开始的 bfs 代码，是在某个节点出队列
 * 之后再更新 visited[curr] = true，这会导致一些问题，
 * 比如先前已经入队的元素由于没有标记为 visited，而重复
 * 加入队列当中。所以应该在进入队列立即进行更新。
 * 
 * 而 dfs 则一般是在 dfs(curr) 的函数体中对 visited[curr]
 * 进行更新。实际上，两种方案对于 dfs 是等效的，因为 dfs 
 * 总是会立即访问下一轮的元素。
 */

struct vertex{
	int nestate = 0;
	int area = 0;
	bool visited = false;
	set<int> edges;
};

struct family{
	int head;
	int size;
	int totalEstate;
	int totalArea;

	bool operator<(const family& right) const{
		double avgArea1 = (double)totalArea / size;
		double avgArea2 = (double)right.totalArea / right.size;
		if(avgArea1 == avgArea2)
			return head < right.head;
		return avgArea1 > avgArea2;
	}
};

map<int, vertex> graph;

family bfs(int origin){
	int head = origin, curr;
	int size = 0, totalEstate = 0, totalArea = 0;
	queue<int> q;
	q.push(origin);
	graph[origin].visited = true;
	while(!q.empty()){
		curr = q.front();
		q.pop();

		++size;
		if(curr < head) head = curr;
		totalArea += graph[curr].area;
		totalEstate += graph[curr].nestate;
		for(int edge : graph[curr].edges)
			if(!graph[edge].visited){
                graph[edge].visited = true;
				q.push(edge);
			}
	}
	family ret;
	ret.head = head;
	ret.size = size;
	ret.totalEstate = totalEstate;
	ret.totalArea = totalArea;
	return ret;
}

int main(){
	int N;
	int curr, father, mother, nchild, child, area, nestate;
	scanf("%d", &N);
	for(int ix = 0; ix != N; ++ix){
		scanf("%d %d %d %d", &curr, &father, &mother, &nchild);
		if(graph.find(curr) == graph.end())
			graph[curr] = vertex();
		if(father != -1){
			graph[curr].edges.insert(father);
			if(graph.find(father) == graph.end())
				graph[father] = vertex();
			graph[father].edges.insert(curr);
		}
		if(mother != -1){
			graph[curr].edges.insert(mother);
			if(graph.find(mother) == graph.end())
				graph[mother] = vertex();
			graph[mother].edges.insert(curr);
		}
		while(nchild--){
			scanf("%d", &child);
			graph[curr].edges.insert(child);
			if(graph.find(child) == graph.end())
				graph[child] = vertex();
			graph[child].edges.insert(curr);
		}
		scanf("%d %d", &nestate, &area);
		graph[curr].nestate = nestate;
		graph[curr].area = area;
	}

	vector<family> res;
	for(auto e : graph)
		if(!e.second.visited)
			res.push_back(bfs(e.first));
	sort(res.begin(), res.end());
	printf("%d\n", res.size());
	for(family f : res){
		printf("%04d %d %.3f %.3f\n", f.head, f.size,
			   (double)f.totalEstate / f.size,
			   (double)f.totalArea / f.size);
	}
	return 0;
}
