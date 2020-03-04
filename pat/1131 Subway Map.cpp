#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

#define INF (0x7fffffff)

struct node{
	vector<int> line;
	bool visited = false;
	vector<int> neighbors;
};

vector<node> subway(10000);
vector<int> path, seq;
int dest, mintransfer, mindist;

int getline(int one, int two){
	for(int e: subway[two].line)
		if(find(subway[one].line.begin(),
			    subway[one].line.end(), e) !=
			    subway[one].line.end())
			return e;
}

void dfs(int origin, int numtransfer){
	int currline = -1;
	if(!seq.empty())
		currline = getline(seq.back(), origin);
	seq.push_back(origin);
	subway[origin].visited = true;

	if(seq.size() > mindist) goto ret;
	if(origin == dest){
		if(seq.size() < mindist){
			path.assign(seq.begin(), seq.end());
			mindist = seq.size();
			mintransfer = numtransfer;
		}else
		if(numtransfer < mintransfer){
			path.assign(seq.begin(), seq.end());
			mintransfer = numtransfer;
		}
		goto ret;
	}

	int nextline;
	for(int e : subway[origin].neighbors)
		if(!subway[e].visited){
			nextline = getline(origin, e);
			if(currline != -1 && currline != nextline)
				dfs(e, numtransfer + 1);
			else
				dfs(e, numtransfer);
		}
	ret:
	seq.pop_back();
	subway[origin].visited = false;
}

int main(){
	int N, M, curr, prev;
	scanf("%d", &N);
	for(int ix = 1; ix <= N; ++ix){
		scanf("%d %d", &M, &prev);
		subway[prev].line.push_back(ix);
		while(--M){
			scanf("%d", &curr);
			subway[curr].line.push_back(ix);
			subway[curr].neighbors.push_back(prev);
			subway[prev].neighbors.push_back(curr);
			prev = curr;
		}
	}
	int K, src, currline, nextline;
	scanf("%d", &K);
	while(K--){
		scanf("%d %d", &src, &dest);
		mintransfer = mindist = INF;
		dfs(src, 0);
		printf("%d\n", path.size() - 1);
		currline = getline(src, path[1]);
		prev = src;
		for(int ix = 1;; ++ix){
			curr = path[ix];
			if(curr == dest) break;
			nextline = getline(curr, path[ix + 1]);
			if(currline != nextline){
				printf("Take Line#%d from %04d to %04d.\n",
					    currline, prev, curr);
				prev = curr;
			}
			currline = nextline;
		}
		printf("Take Line#%d from %04d to %04d.\n",
					    currline, prev, curr);
	}
	return 0;
}
