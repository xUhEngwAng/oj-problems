#include <vector>
#include <queue>
#include <string>
#include <iostream>
#include <cstdio>
using namespace std;

struct Block{
	int sender;
	int duetime;
	vector<int> message;
};

struct node{
	vector<int> neighbor;
	vector<int> chain;
	node(){
	    neighbor.reserve(500);
        chain.reserve(500);
	}
};

queue<Block> q;
vector<node> graph;
Block block;
int n, m, t, k;

void update(int currTime){
	while(!q.empty() && q.front().duetime <= currTime){
        for(int e : graph[q.front().sender].neighbor){
            if(graph[e].chain.size() > q.front().message.size())
                continue;
            if(graph[e].chain.size() < q.front().message.size() ||
               graph[e].chain.back() > q.front().message.back()){
                graph[e].chain = q.front().message;
                block.sender = e;
                block.duetime = currTime + t;
                block.message = graph[e].chain;
                q.push(block);
            }
        }
	q.pop();
	}
}

int main(){
	//freopen("201912-4.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int one, two;
	graph.resize(n + 1);
	for(int ix = 0; ix != m; ++ix){
		scanf("%d %d", &one, &two);
		graph[one].neighbor.push_back(two);
		graph[two].neighbor.push_back(one);
	}
	int currTime = 0, a, b, c;
	int beg, pos;
	string str;
	scanf("%d %d", &t, &k);
	cin.ignore();
	while(k--){
		getline(cin, str);
		beg = 0;
        pos = str.find(' ', beg);
        a = stoi(str.substr(beg, pos - beg));
        beg = pos + 1;
        pos = str.find(' ', beg);
        if(pos != -1) b = stoi(str.substr(beg, pos - beg));
        else b = stoi(str.substr(beg));
        //cout << a << ' ' << b << endl;
		//system("pause");
		while(true){
			update(currTime);
			if(currTime == b) break;
			++currTime;
		}
		if(pos == -1){
			printf("%d 0", graph[a].chain.size() + 1);
			for(int e : graph[a].chain)
				printf(" %d", e);
			printf("\n");
		}
		else{
            c = stoi(str.substr(pos + 1));
			graph[a].chain.push_back(c);
			block.sender = a;
			block.duetime = currTime + t;
			block.message = graph[a].chain;
			q.push(block);
		}
	}
	return 0;
}
