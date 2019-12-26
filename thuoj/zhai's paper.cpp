#include <vector>
#include <algorithm>
#include <stdio.h>

#define DIVISOR ((int)1E9 + 7)

class entry{
public:
	int number;
	int remainingTime;
	entry() = default;
	entry(int number, int time):number(number), remainingTime(time){}
	bool operator<(entry const two) { return remainingTime > two.remainingTime;}
};

class vertex{
public:
	bool exists;
	bool delFlag;
	vertex() :exists(0), delFlag(0) {};
};

using namespace std;
int main(){
	//build graph
	int m, n;
	scanf("%d %d", &n, &m);
	int* weight = new int[n];
	for (int i = 0; i != n; ++i)
		scanf("%d", &weight[i]);
	vector<vector<vertex>> graph(n, vector<vertex>(n, vertex()));
	vector<bool> begins(n, 1);							//a bit map which stores the initial vertices of the graph
	for(int i = 0, one, two; i!= m; ++i){
		scanf("%d %d", &one, &two);
		graph[one - 1][two - 1].exists = 1;
		begins[two - 1] = 0;
	}

	//topological sorting
	long long time = 0;
	long long* early = new long long[n];
	long long* late = new long long[n];
	vector<entry> session;
	for(int ix = 0; ix != n; ++ix){
		if (begins[ix]) {
			session.push_back(entry(ix, weight[ix]));
			early[ix] = 0;
		}
	}
	make_heap(session.begin(), session.end());
	entry curr;
	while(!session.empty()){							//main loop
		pop_heap(session.begin(), session.end());
		curr = session.back();
		session.pop_back();

		time += curr.remainingTime;
		for (auto it = session.begin(); it != session.end(); ++it)
			it->remainingTime -= curr.remainingTime;

		for (int ix = 0, jx; ix != n; ++ix) {
			if (graph[curr.number][ix].exists) {
				graph[curr.number][ix].delFlag = 1;
				for (jx = 0; jx != n; ++jx)
					if (graph[jx][ix].exists && !graph[jx][ix].delFlag)
						break;
				if(jx == n){
					early[ix] = time;
					session.push_back(entry(ix, weight[ix]));
					push_heap(session.begin(), session.end());
				}
			}
		}
	}

	//reverse topological sorting
	long long time_back = time;
	for (int ix = 0, jx; ix != n; ++ix) {
		for (jx = 0; jx != n; ++jx)
			if (graph[ix][jx].exists) break;
		if (jx == n) {
			session.push_back(entry(ix, weight[ix]));
			late[ix] = time_back - weight[ix];
		}
	}
	make_heap(session.begin(), session.end());
	while(!session.empty()){							//main loop
		pop_heap(session.begin(), session.end());
		curr = session.back();
		session.pop_back();

		time_back -= curr.remainingTime;
		for (auto it = session.begin(); it != session.end(); ++it)
			it->remainingTime -= curr.remainingTime;

		for (int ix = 0, jx; ix != n; ++ix) {
			if (graph[ix][curr.number].exists) {
				graph[ix][curr.number].exists = 0;
				for (jx = 0; jx != n; ++jx)
					if (graph[ix][jx].exists)
						break;
				if(jx == n){
					late[ix] = time_back - weight[ix];
					session.push_back(entry(ix, weight[ix]));
					push_heap(session.begin(), session.end());
				}
			}
		}
	}

	//mod
	long long result = 1;
	for(int ix = 0; ix != n; ++ix){
		result *= late[ix] - early[ix] + 10;
		if (result >= DIVISOR) result = result % DIVISOR;
	}

	printf("%lld\n", time);
	printf("%lld", result);

	return 0;
}