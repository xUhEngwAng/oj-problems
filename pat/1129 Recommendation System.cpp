#include <set>
#include <cstdio>
#include <vector>
using namespace std;

/*
 * 这个题够有意思啊！是个数据结构题我感觉。对于每一个 query
 * 都需要在 O(logn) 时间内给出前几个访问次数最大的商品，因
 * 此需要好好设计底层的数据结构。
 *
 * 我的解法是用到了一个 set<int>，来保存所有访问过的商品，
 * 再引入一个 vector<int> 来保存所有商品的访问次数。通过自
 * 定义 set 的比较函数，使得 set 中的元素按照 访问次数降序，
 * 商品 id 升序排列。
 *
 * 每当有一个新的 query，就输出 set 中的前几项商品，更新当前
 * 访问商品的计数信息，然后将该商品在 set 中删除，再重新插入，
 * 来得到新的排序信息。需要注意的是给 set 自定义比较函数的方法，
 * 是 set<int, cmp>，其中 cmp 需要是一个函数类，重载其 () 
 * 运算符。
 */

#define MIN(X, Y) (X < Y? X: Y)

vector<int> cnt;

class cmp{
public:
    bool operator()(int one, int two){
        if(cnt[one] != cnt[two])
            return cnt[one] > cnt[two];
        return one < two;
    }
};

int main(){
	int N, K, curr;
	scanf("%d %d", &N, &K);
	set<int, cmp> recomm;
	cnt = vector<int>(N + 1, 0);
	scanf("%d", &curr);
	cnt[curr]++;
	recomm.insert(curr);

	int itcnt;
	set<int>::iterator it;
	for(int ix = 1; ix != N; ++ix){
		scanf("%d", &curr);
		printf("%d:", curr);
		itcnt = MIN(K, recomm.size());
		it = recomm.begin();
		while(itcnt--){
			printf(" %d", *it);
			++it;
		}
		printf("\n");
		recomm.erase(curr);
		cnt[curr]++;
		recomm.insert(curr);
	}
	return 0;
}
