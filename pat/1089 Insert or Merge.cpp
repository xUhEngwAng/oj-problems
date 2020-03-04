#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

/*
 * 这个题本身的思路是简单的，我是分别模拟插入排序和归并排序，
 * 不断将中间结果与第二个串进行比较，相等时输出即可。
 *
 * 一开始有一个测试点没有通过，后来把插入排序的起始点从 0 改
 * 为 1 就通过了，感觉有点迷惑。我猜想应该是存在一个测试点，
 * 它的两个序列是相同的，即经过一次插入排序后并没有改变原序列，
 * 起始点为 0 时是输出 insertion_once(seq, 1) 得到的序列，
 * 而起始点为 1 时是输出 insertion_once(seq, 2) 的序列。这种
 * 情况应该输入题意不明吧，感觉不是我的问题。
 */

void insertion_once(vector<int> &seq, int pos){
	int tmp = seq[pos];
	while(--pos >= 0 && seq[pos] > tmp){
		seq[pos + 1] = seq[pos];
	}
	seq[pos + 1] = tmp;
}

void merge_once(vector<int> &seq, int cnt){
	vector<int>::iterator start = seq.begin(), last;
	while(start < seq.end()){
		if(start + cnt > seq.end()) last = seq.end();
		else last = start + cnt;
		sort(start, last);
		start += cnt;
	}
}

int main(){
	vector<int> input, res, tmp;
	int N;
	scanf("%d", &N);
	input.resize(N);
	res.resize(N);
	for(int ix = 0; ix != N; ++ix)
		scanf("%d", &input[ix]);
	for(int ix = 0; ix != N; ++ix)
		scanf("%d", &res[ix]);
	bool flag = false;
	tmp.assign(input.begin(), input.end());
	for(int ix = 1; ix != N; ++ix){
		insertion_once(tmp, ix);
		if(tmp == res){
			printf("Insertion Sort\n");
			insertion_once(tmp, ix + 1);
			printf("%d", tmp.front());
			for(int jx = 1; jx != tmp.size(); ++jx)
				printf(" %d", tmp[jx]);
			printf("\n");
			return 0;
		}
	}
	tmp.assign(input.begin(), input.end());
	int cnt = 2;
	while(true){
		merge_once(tmp, cnt);
		if(tmp == res){
			printf("Merge Sort\n");
			merge_once(tmp, cnt * 2);
			printf("%d", tmp.front());
			for(int jx = 1; jx != tmp.size(); ++jx)
				printf(" %d", tmp[jx]);
			printf("\n");
			return 0;
		}
        cnt = cnt << 1;
	}
}
