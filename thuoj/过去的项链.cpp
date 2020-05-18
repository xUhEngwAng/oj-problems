#include <cstdio>
#include <iostream>
using std::cin;
#define MAXN (200002)

int start[MAXN], end[MAXN], arr[MAXN];
int N;

void init(){
	start[0] = end[N + 1] = 0;
	for(int ix = 1; ix <= N; ++ix){
		end[ix] = arr[ix];
		if(end[ix-1] > 0) end[ix] += end[ix-1];
	}
	for(int ix = N; ix >= 0; --ix){
		start[ix] = arr[ix];
		if(start[ix + 1] > 0) start[ix] += start[ix+1];
	}
}

void update(int left, int right){
	int pos;
	for(int ix = left; ix <= right; ++ix){
		pos = left + right - ix;
		end[ix] = arr[pos];
		if(end[ix-1] > 0) end[ix] += end[ix-1];
	}
	for(int ix = right + 1; ix <= N; ++ix){
		end[ix] = arr[ix];
		if(end[ix-1] > 0) end[ix] += end[ix-1];
	}
	for(int ix = right; ix >= left; --ix){
		pos = left + right - ix;
		start[ix] = arr[pos];
		if(start[ix+1] > 0) start[ix] += start[ix+1];
	}
	for(int ix = left - 1; ix >= 0; --ix){
		start[ix] = arr[ix];
		if(start[ix+1] > 0) start[ix] += start[ix+1];
	}
}

long long compute(){
	long long curr, max = 0;
	for(int ix = 1; ix <= N; ++ix){
		curr = start[ix] + end[ix] - arr[ix];
		if(curr > max) max = curr;
	}
	return max;
}

int main(){
	long long max = 0, curr;
	scanf("%d", &N);
	for(int ix = 1; ix <= N; ++ix)
		scanf("%d", arr + ix);
	init();
	for(int left = 1; left != N; ++left)
	for(int right = left + 1; right <= N; ++right){
		/*for(int ix = 1; ix <= N; ++ix)
			printf("%d ", end[ix]);
		printf("\n");
		for(int ix = 1; ix <= N; ++ix)
			printf("%d ", start[ix]);
		printf("\n");
		cin.ignore();*/

		update(left, right);
		curr = compute();
		if(curr > max) max = curr;
	}
	printf("%lld\n", max);
	return 0;
}
