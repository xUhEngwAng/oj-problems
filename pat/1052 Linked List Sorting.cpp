#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

/*
 * 这个题我拿到一看，『这么简单，我五分钟就能写出来』。一小时后，
 * 『我的代码没问题啊，可能会通不过呢？』这里是存在两个问题：
 *
 * 1. 一开始对题意的理解不对。我一开始的解法是直接对所有输入的
 *    结点排序，然后输出即可。然而输出的结点中，可能存在无效的
 *    结点，即不在起始结点所在的链上。
 * 2. 一个细节问题，卡了我半天。输出的第一行的起始地址格式，我
 *    忘了加 %05d......
 */

struct list_node{
    int next;
    int value;
};

struct node{
	int value;
	int addr;
	node() = default;
	node(int v, int a): value(v), addr(a){}
};

bool cmp(const node& one, const node& two){
	return one.value < two.value;
}

list_node *table = new list_node[100000];

int main(){
	int curr, N, origin;
	scanf("%d %d", &N, &origin);
	vector<node> data;
	data.reserve(N);
	for(int ix = 0; ix != N; ++ix){
        scanf("%d", &curr);
		scanf("%d %d", &table[curr].value, &table[curr].next);
	}
    for(curr = origin; curr != -1;){
        data.emplace_back(table[curr].value, curr);
        curr = table[curr].next;
    }
    N = data.size();
    if(N == 0){
        printf("0 -1\n");
        return 0;
    }

    sort(data.begin(), data.end(), cmp);

	printf("%d %05d\n", N, data[0].addr);
	for(int ix = 0; ix != N - 1; ++ix){
		printf("%05d %d %05d\n", data[ix].addr,
                data[ix].value, data[ix + 1].addr);
	}
	printf("%05d %d -1\n", data[N - 1].addr, data[N - 1].value);
	return 0;
}
