#include <cstdio>

/*
 * 这个题本身是非常简单，但是我犯了一个非常愚蠢的错误。
 * 题目中给出了所有节点的数目是 N，但是这 N 个节点未必
 * 都是在链表上的，所以输出的时候，应该以计数值 count
 * 来作为循环终止条件，而不是 N。
 */

struct node{
	int data;
	int next;
};

struct res_node{
	int data;
	int addr;
};

node *list = new node[100000];
res_node *res = new res_node[100000];

int main(){
	int N, K, root;
	scanf("%d %d %d", &root, &N, &K);
	int addr, data, next;
	for(int ix = 0; ix != N; ++ix){
		scanf("%d %d %d", &addr, &data, &next);
		list[addr].data = data;
		list[addr].next = next;
	}

	addr = root;
	int count = 0;
	while(addr != -1){
		if(list[addr].data < 0){
			res[count].addr = addr;
			res[count].data = list[addr].data;
			++count;
		}
		addr = list[addr].next;
	}

	addr = root;
	while(addr != -1){
		if(list[addr].data >= 0 && list[addr].data <= K){
			res[count].addr = addr;
			res[count].data = list[addr].data;
			++count;
		}
		addr = list[addr].next;
	}

	addr = root;
	while(addr != -1){
		if(list[addr].data > K){
			res[count].addr = addr;
			res[count].data = list[addr].data;
			++count;
		}
		addr = list[addr].next;
	}

	for(int ix = 0; ix < count - 1; ++ix)
		printf("%05d %d %05d\n", res[ix].addr, res[ix].data, res[ix + 1].addr);
	printf("%05d %d -1\n", res[count - 1].addr, res[count - 1].data);
	return 0;
}
