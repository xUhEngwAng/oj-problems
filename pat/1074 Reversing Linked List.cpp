#include <stack>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define BASE (100000)

struct node{
	int value;
	int next;
};

node *table = new node[100001]; //100,000 reserved

int main(){
	int origin, N, K, addr;
	scanf("%d %d %d", &origin, &N, &K);
	for(int ix = 0; ix != N; ++ix){
		scanf("%d", &addr);
		scanf("%d %d", &table[addr].value, &table[addr].next);
	}
	table[BASE].next = origin;

	int prev = BASE, curr = origin, count = 0;
	stack<int> s;
	while(true){
        count = 0;
		while(count < K){
			if(curr == -1) break;
			s.push(curr);
			++count;
			curr = table[curr].next;
		}
		if(count != K) break;
		while(count--){
			table[prev].next = s.top();
			s.pop();
			prev = table[prev].next;
		}
		table[prev].next = curr;
	}
	curr = table[BASE].next;
	while(table[curr].next != -1){
		printf("%05d %d %05d\n", curr, table[curr].value, table[curr].next);
		curr = table[curr].next;
	}
	printf("%05d %d -1\n", curr, table[curr].value);
	return 0;
}
