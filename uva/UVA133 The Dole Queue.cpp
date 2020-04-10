#include <cstdio>

/*
 * 这个题我一开始的实现是基于向量的，会做实质的删除操作，
 * 这样对指针位置的管理会非常复杂，最后放弃了......
 *
 * 我看紫书上面的解答，其实也是基于向量，只不过是采用懒惰
 * 删除的策略，给被删除元素一个标记。这种想法我一开始也是
 * 想过的，只不过觉得效率太低了而作罢......
 *
 * 最终是基于双向循环链表来实现的，这样删除操作相对简单，
 * 只需要保存下一次起始的指针即可。这里有一个注意事项，
 * 是说如果两个操作指针紧邻，即第二个操作指针恰好在第一个
 * 的右边，删除操作则会产生问题。解决方案是对这种情况进行
 * 检测，如果确实发生，则将两个指针交换位置即可。
 */

struct list_entry{
	list_entry *left;
	list_entry *right;
	int value;
};

list_entry *head, *tail;

void list_init(){
	head = new list_entry;
	tail = new list_entry;
	head->right = tail;
	head->left = tail;
	tail->right = head;
	tail->left = head;
}

void list_insert_before(list_entry *node, int value){
	list_entry *tmp = new list_entry;
	tmp->value = value;
	tmp->left  = node->left;
	node->left->right = tmp;
	tmp->right = node;
	node->left = tmp;
}

list_entry* list_left(list_entry *node){
	list_entry *res = node->left;
	if(res == head) res = tail->left;
	return res;
}

list_entry* list_right(list_entry *node){
	list_entry *res = node->right;
	if(res == tail) res = head->right;
	return res;
}

void list_delete(list_entry *node){
	list_entry *prev = node->left;
	list_entry *succ = node->right;
	prev->right = succ;
	succ->left  = prev;
}

int main(){
	int n, m, k, step1, step2, one, two;
	list_entry *first, *second;
	while(true){
		scanf("%d %d %d", &n, &k, &m);
		if(n == 0) break;
		list_init();
		for(int ix = 1; ix <= n; ++ix){
			list_insert_before(tail, ix);
		}
		first = head;
		second = tail;
		while(n){
			step1 = k % n;
			if(step1 == 0) step1 = n;
			step2 = m % n;
			if(step2 == 0) step2 = n;
			while(step1--) first = list_right(first);
			while(step2--) second = list_left(second);
			if(first == second){
				one = first->value;
				printf("% 3d", one);
				list_delete(first);
				if(--n) printf(",");
			}
			else{
				one = first->value;
				two = second->value;
				printf("% 3d% 3d", one, two);
				if(list_right(first) == second){
					first = list_right(first);
					second = list_left(second);
				}
				list_delete(first);
				list_delete(second);
				n -= 2;
				if(n) printf(",");
			}
		}
		printf("\n");
	}
	return 0;
}