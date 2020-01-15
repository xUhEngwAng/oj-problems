#include <algorithm>
#include <cstdio>
#include <cstring>

#define VERSION2

using namespace std;

/*
 * 这个题我还以为会超时，没想到居然A了，PAT的数据确实不行...
 * 本题一开始我是想出了两种方案：
 * 1. 下面实现的方案，首先对所有数据进行排序；对于每一个查询
 *    进行一次遍历找出前 M 个符合条件的元素。每次查询为O(n)。
 * 2. 对年龄进行排序，对于每个查询，首先在 O(logn) 时间内确
 *    定年龄范围。然后将该范围的数据拷贝到另一个 vector 中，
 *    对该 vector 使用 make_heap, pop_heap 等相关操作。该方
 *    案拷贝元素的时间最差为O(n)，建堆时间也是O(n)，后续的堆
 *    操作只需要O(Mlogn)。感觉说不定是可行的，但是因为我不会
 *    make_heap 这几个函数而作罢。之后可能实现一下这个方案。  
 */

struct entry{
	int age;
	int wealth;
	char name[9];

	entry() = default;
	entry(int age): age(age){}

	bool operator<(const entry& two){
        if(wealth != two.wealth)
            return wealth < two.wealth;
        if(age != two.age)
            return age > two.age;
        return strcmp(name, two.name) > 0;
	}
};

bool cmp1(entry one, entry two){
	if(one.wealth != two.wealth)
		return one.wealth > two.wealth;
	if(one.age != two.age)
		return one.age < two.age;
	return strcmp(one.name, two.name) < 0;
}

#ifdef VERSION1

int main(){
	int N, K, M;
	int lo, hi, count;
	scanf("%d %d", &N, &K);
	entry *datas = new entry[N];
	for(int ix = 0; ix != N; ++ix)
		scanf("%s %d %d", datas[ix].name, &datas[ix].age, &datas[ix].wealth);
	sort(datas, datas + N, cmp1);
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

#else

//VERSION 2

/*
 * 实现了上面说的版本2，需要注意的点还是蛮多的：
 * 1. 对原始数据排序后，调用 lower_bound, upper_bound 确定范围。
 *    这里仍然需要提供比较函数。
 * 2. make_heap, pop_heap 也需要提供比较函数，我这里是重载了 < 
 *    运算符。
 * 3. 把数组 assign 给向量，v.assign(first_pointer, last_pointer)
 *    这里的指针和正常的迭代器是一致的，并且都是前闭后开区间。
 * 结果数据量最大的第二个测试点快了两倍多，然而第三个测试点居然
 * 超时了？！我佛了。
 */

bool cmp2(entry one, entry two){
	return one.age < two.age;
}

int main(){
	int N, K, M;
	int lo, hi, count;
	int begin, end;
	scanf("%d %d", &N, &K);
	entry *datas = new entry[N];
	vector<entry> heap;
	heap.reserve(N);
	for(int ix = 0; ix != N; ++ix)
		scanf("%s %d %d", datas[ix].name, &datas[ix].age, &datas[ix].wealth);
	sort(datas, datas + N, cmp2);

	for(int ix = 0; ix != K; ++ix){
		count = 0;
		scanf("%d %d %d", &M, &lo, &hi);
		printf("Case #%d:\n", ix + 1);

		begin = lower_bound(datas, datas + N, entry(lo), cmp2) - datas;
		end   = upper_bound(datas, datas + N, entry(hi), cmp2) - datas;
		heap.assign(datas + begin, datas + end);
		make_heap(heap.begin(), heap.end());
		while(!heap.empty() && count < M){
			pop_heap(heap.begin(), heap.end());
			printf("%s %d %d\n", heap.back().name, heap.back().age, heap.back().wealth);
			heap.pop_back();
			++count;
		}
		if(count == 0) printf("None\n");
	}
	return 0;
}

#endif
