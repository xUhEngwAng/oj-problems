#include <algorithm>
#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;

#define MAX (~(1 << 31))

struct Pair{
	int one;
	int two;

	Pair() = default;
	Pair(int first, int second): one(first), two(second){}
};

int main(){
	int N, M;
	scanf("%d %d", &N, &M);
	int *arr = new int[N + 1], tmp;
	arr[0] = 0;
	for(int ix = 1; ix <= N; ++ix){
		scanf("%d", &tmp);
		arr[ix] = arr[ix - 1] + tmp;
	}
	int minCost = MAX, pos;
	vector<Pair> res;
	for(int ix = 1; ix <= N; ++ix){
		pos = lower_bound(arr + ix, arr + N + 1, M + arr[ix - 1]) - arr;
		if(pos > N) continue;
		if(arr[pos] - arr[ix - 1] < minCost){
			res.clear();
			res.emplace_back(ix, pos);
			minCost = arr[pos] - arr[ix - 1];
		}else
		if(arr[pos] - arr[ix - 1] == minCost)
			res.emplace_back(ix, pos);
		else;
	}
	for(auto e : res){
		printf("%d-%d\n", e.one, e.two);
	}
	return 0;
}
