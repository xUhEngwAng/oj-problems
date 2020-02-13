#include <vector>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

struct res_pair{
	int first;
	int second;
	res_pair() = default;
	res_pair(int one, int two): first(one), second(two){}

	bool operator<(const res_pair& right){
		if(first != right.first)
			return first < right.first;
		return second < right.second;
	}
};

int main(){
	int N, M, one, two, count;
	scanf("%d %d", &N, &M);
	vector<int> map(10000, -1), unmap(N);
	vector<vector<bool>> graph(N, vector<bool>(N, false));
	count = 0;
	for(int ix = 0; ix != M; ++ix){
		scanf("%d %d", &one, &two);
		if(map[abs(one)] == -1){
			map[abs(one)] = count;
			unmap[count] = one;
			++count;
		}
		if(map[abs(two)] == -1){
			map[abs(two)] = count;
			unmap[count] = two;
			++count;
		}
		graph[map[abs(one)]][map[abs(two)]] = true;
		graph[map[abs(two)]][map[abs(one)]] = true;
	}
	int K, a, b;
	scanf("%d", &K);
	vector<res_pair> res;
	while(K--){
		scanf("%d %d", &a, &b);
		one = map[abs(a)];
		two = map[abs(b)];
		if(one == -1 || two == -1){
            printf("0\n");
            continue;
		}
		for(int ix = 0; ix != N; ++ix){
			if(graph[one][ix] && ix != two &&
			   ((a > 0 && unmap[ix] > 0) ||
			    (a < 0 && unmap[ix] < 0)))
				for(int jx = 0; jx != N; ++jx)
					if(graph[two][jx] && jx != one &&
			   		  ((b > 0 && unmap[jx] > 0) ||
			    	   (b < 0 && unmap[jx] < 0)))
						if(graph[ix][jx])
							res.emplace_back(abs(unmap[ix]), abs(unmap[jx]));
		}
		sort(res.begin(), res.end());
		printf("%d\n", res.size());
		for(auto e : res)
			printf("%d %d\n", e.first, e.second);
        res.clear();
	}
	return 0;
}
