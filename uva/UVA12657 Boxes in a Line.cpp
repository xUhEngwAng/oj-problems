#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * 从逻辑上来看，此题是非常简单的，只需要手写一个链表即可。
 * 这里直接用 std::list 感觉是行不通的。但是手写链表过程中
 * 毕竟涉及到不少指针操作，还是蛮容易出错的，调试起来不太
 * 方便。
 *
 * 我的实现和紫书上的参考答案基本是一致的，对于 reverse
 * 操作也和紫书一样，是采用一种懒惰的实现，即用一个标记来
 * 表示当前链表是否应该是反转的。这样，操作1和2也要做相应
 * 的修改，即如果 isReverse := true，那么操作1,2分别要
 * 插入到右边和左边。
 *
 * 我这里一个细节问题是，本来我是用一个 bool 来保存 isReverse
 * 的，对它的更新采用 isReverse = ~isReverse，但是似乎没有
 * 作用，后来改成用 int 来保存就没有问题了，原因至今未明。然后
 * 把 bool 类型的 isReverse 改成 isReverse = !isReverse 
 * 也是可以工作的。为什么 bool 不可以按位取反呢？
 *
 * 我的实现中也存在一些不足，比如我是用指针来实现链表的，但是
 * 完全可以用数组来存储啊，这样实现起来会简单不少，紫书上就是
 * 这样做的。
 */

struct list_entry{
	int value;
	list_entry *left;
	list_entry *right;
};

list_entry *head, *tail;

void list_init(){
	head->left = tail;
	head->right = tail;
	tail->left = head;
	tail->right = head;
}

list_entry* list_insert_before(list_entry* succ, int value){
	list_entry *node = new list_entry;
	node->value = value;
	list_entry *prev = succ->left;
	node->left = prev;
	node->right = succ;
	prev->right = node;
	succ->left = node;
	return node;
}

void list_delete(list_entry *node){
	list_entry *prev = node->left;
	list_entry *succ = node->right;
	prev->right = succ;
	succ->left  = prev;
}

int main(){
    freopen("1.out", "w", stdout);
	int n, m, cnt = 1;
    bool isReverse;
	vector<list_entry*> map;
	head = new list_entry;
	tail = new list_entry;
	while(scanf("%d %d", &n, &m) == 2){
		list_init();
		map.resize(n + 1);
		for(int ix = 1; ix <= n; ++ix)
			map[ix] = list_insert_before(tail, ix);
		printf("Case %d: ", cnt++);
		isReverse = 0;
		int op, one, two;
		list_entry *left, *right, *prev, *succ;
		while(m--){
			scanf("%d", &op);
			if(op == 4) isReverse = !isReverse;
			else{
				scanf("%d %d", &one, &two);
				if(op == 3){
					swap(map[one]->value, map[two]->value);
					swap(map[one], map[two]);
				}else{
					left = map[one];
					right = map[two];
					list_delete(left);
					if((op == 1 && !isReverse) || (op == 2 && isReverse)){
						prev = right->left;
						left->left = prev;
						left->right = right;
						prev->right = left;
						right->left = left;

					}else{
						succ = right->right;
						left->left = right;
						left->right = succ;
						right->right = left;
						succ->left = left;
					}
				}
			}
            /*
            for(list_entry *curr = head->right; curr != tail; curr = curr->right)
                printf("%d ", curr->value);
            printf("\n");*/

		}
		long long res = 0;
		list_entry *curr;
		if(!isReverse){
            curr = head->right;
            for(int ix = 1; curr != tail; ++ix, curr = curr->right)
                if(ix & 1) res += curr->value;
		}
        else{
            curr = tail->left;
            for(int ix = 1; curr != head; ++ix, curr = curr->left)
                if(ix & 1) res += curr->value;
        }
		printf("%lld\n", res);
	}
	return 0;
}
