#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

/* 
 * 本题就是一个 stl 水题啊，但是还是有一些收获。
 * 1. 超级大的数据量时，使用 char* 而不是 string，使用 scanf
 *    而不是 cin/cout 真的会显著提升时间性能。一开始我就是用
 *    string 以及 cin/cout 超时了，改了之后好像快了四倍！
 * 2. 参考答案的解法甚至还觉得对字符串排序需要大量移动，所以
 *    用了表排序来避免这部分开销。感觉实现起来比我想象中简单
 *    很多，有机会学习一下。但是对字符串排序难道不是移动指针？
 *    以后可以探索探索。
 */

bool cmp(char* one, char* two){
	return strcmp(one, two) < 0;
}

int main(){
	int N, K;
	scanf("%d %d", &N, &K);
	vector<vector<char*>> courseList(K);
	char *name;
	int count, currCourse;
	for(int ix = 0; ix != N; ++ix){
        name = new char[5];
		scanf("%s %d", name, &count);
		while(count--){
			scanf("%d", &currCourse);
			courseList[currCourse - 1].push_back(name);
		}
	}

	count = 1;
	for(auto e : courseList){
		sort(e.begin(), e.end(), cmp);
		printf("%d %d\n", count++, e.size());
		for(auto it = e.begin(); it != e.end(); ++it)
			printf("%s\n", *it);
	}
	return 0;
}
