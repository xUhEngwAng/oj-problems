/*
 * 这个题让我觉得我真的不适合写代码。前两个版本是我自己想的，
 * 反正都会超时，当然了这个题有它的特殊性，我可以自己跑出来
 * 答案，然后提交的时候直接printf就可以了。
 * 我给出的两个版本思路几乎是相同的，都是逐个判断每个整数是否
 * 满足丑数的定义，然而这里的第1500个丑数大约是8亿多，两个方
 * 案都需要进行这么多次循环，超时是显而易见的。
 * 看刘汝佳老师给的答案，居然是用一个优先级队列！逐个取出最小
 * 的丑数然后产生三个新的，需要注意的是同一个丑数可以有多种方
 * 法生成，因此要注意识别。这种方案的时间复杂度只有O(mlogm)，
 * m为丑数的个数，这里m = 1500。
 * 通过这个题的确学到了不少知识点，比如
 * 1. 优先级队列指定比较函数的方法，此时需要同时指定底层容器。
 * 2. lower_bound的使用方法，对于数组是使用两个地址来指定边
 * 界，返回值也是找到的元素的地址。
 */

#define VERSION3

#ifdef VERSION1
#include <cstdio>

int main(){
	int count = 1;
	int curr = 2, tmp;
	while(count < 1500){
        tmp = curr;
		while((tmp & 1) == 0)
			tmp = tmp >> 1;
		while(tmp % 5 == 0)
			tmp = tmp / 5;
		while(tmp % 3 == 0)
			tmp = tmp / 3;
		if(tmp == 1) count++;
		++curr;
	}
	printf("The 1500'th ugly number is %d", curr - 1);

	//printf("The 1500'th ugly number is 859963392.\n");
	return 0;
}

#elif VERSION2

//Version 2
#include <algorithm>
#include <cstdio>
using namespace std;

int main(){
	int ugly_num[1500];
	ugly_num[0] = 1;

	int size = 1;
	int curr = 1;
	int tmp, pos;
	while(size < 1500){
		++curr;
		if((curr & 1) == 0) tmp = curr >> 1;
		else if(curr % 5 == 0) tmp = curr / 5;
		else if(curr % 3 == 0) tmp = curr / 3;
		else continue;
		pos = lower_bound(ugly_num, ugly_num + size, tmp) - ugly_num;
		if(ugly_num[pos] == tmp){
			ugly_num[size++] = curr;
		}
	}
	printf("The 1500'th ugly number is %d", curr);
}

#else//VERSION3

#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

typedef long long LL;

int main(){
    priority_queue<LL, vector<LL>, greater<LL>> pq;
    pq.push(1);
    int count = 0;
    LL curr, prev = 0;
    while(count < 1500){
        curr = pq.top();
        pq.pop();
        //printf("curr: %d\n", curr);
        if(curr == prev) continue;
        pq.push(curr << 1);
        pq.push(curr * 3);
        pq.push(curr * 5);
        prev = curr;
        ++count;
        //printf("count: %d\n", count);
    }
    printf("The 1500'th ugly number is %lld", curr);
}

#endif
