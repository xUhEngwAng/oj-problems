#include <cstdio>
#include <string>
#include <stack>
#include <iostream>
using namespace std;

/*
 * 这个题还是有一点意思的，遇到了一些问题：
 *
 * 1. scanf("%c", &ch) 是会读入空格的，因此必须手动在 scanf
 *    中加入空格来忽略输入中的空格。
 * 2. 我感觉此题的题意不是很明朗，比如两个串的共同后缀是否一定
 *    共用链表结点，比如 being 和 loading 可不可以只共用 ng
 *    的结点呢？我的第一个解答就是假定上面的情况不会发生，结果
 *    最后一个测试点过不了。
 * 3. 所以后来写了第二个版本，是用两个栈分别保存两个串的逆序，
 *    逐个判断栈顶来确定第一个共享结点。看《算法笔记》上的解答，是
 *    直接寻找两个串的第一个公共结点，一开始我觉得此方案不严谨，
 *    因为两个串应该也可以在前面部分也共享一些结点，比如 
 *    eating 和 being 共享 e 和 ing。现在我明白这种情况是不能
 *    发生的，如果共享 e，那么 e.next 应该也会相同才是。
 */

#define VERSION2

struct node{
	char ch;
	int next;
};

node *table = new node[100000];

#ifdef VERSION1

int main(){
	int addr1, addr2, N, curr;
	scanf("%d %d %d", &addr1, &addr2, &N);
	for(int ix = 0; ix != N; ++ix){
		scanf("%d", &curr);
		scanf(" %c %d", &(table[curr].ch), &(table[curr].next));
	}

	string one, two;
	for(curr = addr1; curr != -1;){
		one.push_back(table[curr].ch);
		curr = table[curr].next;
	}
	for(curr = addr2; curr != -1;){
		two.push_back(table[curr].ch);
		curr = table[curr].next;
	}

	int count = 0;
	for(int ix = one.size() - 1, jx = two.size() - 1;
		ix >= 0 && jx >= 0; --ix, --jx)
		if(one[ix] != two[jx]) break;
		else ++count;

	if(count == 0){
		printf("-1\n");
		return 0;
	}
	count = one.size() - count;
	curr = addr1;
	while(count--){
		curr = table[curr].next;
	}
	printf("%05d\n", curr);
	return 0;
}

#else

int main(){
    int addr1, addr2, N, curr;
	scanf("%d %d %d", &addr1, &addr2, &N);
	for(int ix = 0; ix != N; ++ix){
		scanf("%d", &curr);
		scanf(" %c %d", &(table[curr].ch), &(table[curr].next));
	}
	stack<int> one, two;
	for(curr = addr1; curr != -1;){
		one.push(curr);
		curr = table[curr].next;
	}
	for(curr = addr2; curr != -1;){
		two.push(curr);
		curr = table[curr].next;
	}

    while(!one.empty() && !two.empty() && one.top() == two.top()){
        curr = one.top();
        one.pop();
        two.pop();
    }
    if(curr == -1) printf("-1\n");
    printf("%d\n", curr);
    return 0;
}

#endif
