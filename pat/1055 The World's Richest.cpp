#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

/*
 * 这个题我还以为会超时，没想到居然A了，PAT的数据确实不行。
 * 本题一开始我是想出了两种方案：
 * 1. 下面实现的方案，首先对所有数据进行排序；对于每一个查询
 *    进行一次遍历找出前 M 个符合条件的元素。每次查询为O(n)。
 * 2. 对年龄进行排序，对于每个查询，首先在 O(logn) 时间内确
 *    定年龄范围。然后将该范围的数据拷贝到另一个 vector 中，
 *    对该 vector 使用 make_heap, pop_heap 等相关操作。该方
 *    案拷贝元素的时间最差为O(n)，后续的堆操作只需要 O(Mlogn)
 *    的时间。感觉说不定是可行的，但是因为我不会 make_heap 这
 *    几个函数而作罢。之后可能实现一下这个方案。
 */

struct entry{
	int age;
	int wealth;
	char name[9];
};

bool cmp(entry one, entry two){
	if(one.wealth != two.wealth)
		return one.wealth > two.wealth;
	if(one.age != two.age)
		return one.age < two.age;
	return strcmp(one.name, two.name) < 0;
}

int main(){
	int N, K, M;
	int lo, hi, count;
	scanf("%d %d", &N, &K);
	entry *datas = new entry[N];
	for(int ix = 0; ix != N; ++ix)
		scanf("%s %d %d", datas[ix].name, &datas[ix].age, &datas[ix].wealth);
	sort(datas, datas + N, cmp);
	for(int ix = 0; ix != K; ++ix){
		scanf("%d %d %d", &M, &lo, &hi);
		count = 0;
		printf("Case #%d:\n", ix + 1);
		for(int jx = 0; jx != N; ++jx){
			if(datas[jx].age >= lo && datas[jx].age <= hi){
				printf("%s %d %d\n", datas[jx].name, datas[jx].age, datas[jx].wealth);
				if(++count == M) break;
			}
		}
		if(count == 0) printf("None\n");
	}
	return 0;
}
