#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

/*
 * 本题看似简单，然而在实现过程中仍然遇到了一些问题。
 * 1. C style字符串的处理很不熟悉，中间字符串的比较直接就用了
 *    比较运算符，然后 strcpy 的参数顺序也忘了，应该是把后面
 *    的拷贝到前面的。
 * 2. 犯了一个低级错误，vector<entry> datas(N); 这样直接就
 *    调用默认构造函数创建了 N 个对象了，后面就不能用 emplace_back
 *    而应该修改已创建的对象。
 * 3. 忘了怎么声明一个函数指针，然后分别给它赋 cmp1, cmp2, cmp3
 *    值来简化代码。
 */

struct entry{
	char id[7];
	char name[9];
	int score;

	entry() = default;
	entry(char i[7], char n[9], int s){
        strcpy(id, i);
        strcpy(name, n);
        score = s;
	}
};

bool cmp1(entry one, entry two){
	return strcmp(one.id, two.id) < 0;
}

bool cmp2(entry one, entry two){
	if(strcmp(one.name, two.name) != 0)
        return strcmp(one.name, two.name) < 0;
	return strcmp(one.id, two.id) < 0;
}

bool cmp3(entry one, entry two){
	if(one.score != two.score)
        return one.score < two.score;
	return strcmp(one.id, two.id) < 0;
}

int main(){
	int N, C;
	scanf("%d %d", &N, &C);
	vector<entry> datas;
	datas.reserve(N);
	char id[7], name[8];
	int score;
	for(int ix = 0; ix != N; ++ix){
		scanf("%s %s %d", id, name, &score);
		datas.emplace_back(id, name, score);
	}

	bool (*cmp)(entry, entry);
	if(C == 1) cmp = cmp1;
	else if(C == 2) cmp = cmp2;
	else       cmp = cmp3;
	sort(datas.begin(), datas.end(), cmp);

	for(auto e : datas)
		printf("%s %s %d\n", e.id, e.name, e.score);
	return 0;
}
