#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

/*
 * 这个题目本身是简单的，显而易见，每次都应该选择最短的两段绳子
 * 进行对折，这样最终得到的绳子才会有最长的长度。然而这个结论我却
 * 不会证明，后来找了柳神的博客
 * https://blog.csdn.net/liuchuo/article/details/60467543
 * 才如醍醐灌顶。
 *
 * 由于每次对折都会使选取的两段绳子长度减半，所以越是在前面选择的
 * 绳子，要对折的次数也就越多。这样，就需要长的绳子对折的次数尽可能
 * 少，所以每次都应该选择最短的两段绳子进行对折。由于对折后的绳子
 * 仍然是最短的，因此直接加入序列即可。
 */

int main(){
	int N, curr;
	scanf("%d", &N);
	vector<double> seq;
	for(int ix = 0; ix != N; ++ix){
		scanf("%d", &curr);
		seq.push_back(curr);
	}
	sort(seq.rbegin(), seq.rend());
	double one, two;
	while(seq.size() > 1){
		one = seq.back();
		seq.pop_back();
		two = seq.back();
		seq.pop_back();
		seq.push_back((one + two) / 2);
	}
	printf("%d\n", (int)seq.front());
	return 0;
}
