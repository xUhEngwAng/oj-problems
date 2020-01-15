#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;


struct entry{
	int grade;
	char name[11];
	char id[11];

    entry() = default;
	entry(int grade): grade(grade){}
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
	sort(datas, datas + N, cmp1);
	scanf("%d %d", &lo, &hi);
	auto begin = lower_bound(datas, datas + N, entry(hi), cmp1);
	auto end = upper_bound(datas, datas + N, entry(lo), cmp1);
	int count = 0;
	while(begin < end){
		printf("%s %s\n", begin->name, begin->id);
		++begin, ++count;
	}
	if(count == 0) printf("NONE\n");
	return 0;
}
