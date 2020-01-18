#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * 这个题的思路是非常简单的，问题主要是出在对 stl 的使用不熟悉。
 * 这里主要的问题在于，使用 lower_bound 以及 upper_bound 的过
 * 程中，使用 entry 定义的 < 运算符总是会报错。后来才发现原来应
 * 该将其定义为 const，表示该函数不会对当前对象进行修改，这样才
 * 能保证常量的对象也可以调用该函数。
 * 需要注意的点在于 lower_bound 以及 upper_bound 的返回结果，
 * 前者返回 **第一个不满足 cmp 函数的迭代器**，后者则是返回**
 * 第一个满足 !cmp 函数的迭代器**。这样，当使用默认的 < 比较符
 * 时，lower_bound 返回第一个 **大于或等于** val 的迭代器，而
 * upper_bound 返回第一个 **大于** val 的迭代器。
 */

struct entry{
	int grade;
	char name[11];
	char id[11];

    entry() = default;
	entry(int grade): grade(grade){}

	bool operator<(const entry& two) const {
        return grade > two.grade;
	}
};

bool cmp1(entry one, entry two){
    return one.grade > two.grade;
}

int main(){
	int N, lo, hi;
	scanf("%d", &N);
	entry *datas = new entry[N];
	for(int ix = 0; ix != N; ++ix)
		scanf("%s %s %d", datas[ix].name, datas[ix].id, &datas[ix].grade);
	sort(datas, datas + N);
	scanf("%d %d", &lo, &hi);
	auto begin = lower_bound(datas, datas + N, entry(hi));
	auto end = upper_bound(datas, datas + N, entry(lo));
	int count = 0;
	while(begin < end){
		printf("%s %s\n", begin->name, begin->id);
		++begin, ++count;
	}
	if(count == 0) printf("NONE\n");
	return 0;
}
