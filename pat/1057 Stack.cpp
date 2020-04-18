#include <cstdio>
#include <stack>
#include <cstring>
using namespace std;

/*
 * 没想到 PAT 居然还有这种难度的题目，感觉思维上的难度还挺大
 * 的。此题用暴力的解法比如排序，或者用 set 维护一个有序序列
 * 时间复杂度都至少是 O(N^2)，显然是不可行的。
 *
 * 一种策略是想，建立一个 hashtable 保存每个数字出现的次数。在
 * 每次 PeekMedian 时，只需求这些次数的和，找到第一次大于 N/2
 * 的位置，即为要找的中位数。这种算法的复杂度已经优于上面提到的
 * 算法了。
 *
 * 那既然要求前 k 项的和，不妨引入一个树状数组，在 O(log N )
 * 时间内就可以求到前 k 项的和。以下只需要使用二分查找，找到使
 * 次数之和恰好大于等于 N/2 的位置就可以了。
 *
 * 这里需要注意二分查找的细节。由于和等于 N/2 的位置可能存在多
 * 个，应该找到的乃是第一个位置。另一方面，可能并不存在使和恰好
 * 等于 N/2 的位置，此时应该返回第一个大于 N/2 的位置。因此这里
 * 使用了双分支的二分查找，和邓公讲的那种恰好反过来。
 */

int sum[100001];

int low_bit(int x){
	return x & (-x);
}

void update(int pos, int value){
	while(pos <= 100000){
		sum[pos] += value;
		pos += low_bit(pos);
	}
}

int get_sum(int pos){
	int ret = 0;
	while(pos > 0){
		ret += sum[pos];
		pos -= low_bit(pos);
	}
	return ret;
}

int main(){
	int M, curr, target;
	int lo, hi, mid;
	stack<int> s;
	scanf("%d", &M);
	memset(sum, 0, sizeof(sum));
	char cmd[11];
	while(M--){
		scanf("%s", cmd);
		if(cmd[1] == 'o'){
			if(s.empty()) printf("Invalid\n");
			else{
				printf("%d\n", s.top());
				update(s.top(), -1);
				s.pop();
			}
		}else
		if(cmd[1] == 'u'){
			scanf("%d", &curr);
			s.push(curr);
			update(curr, 1);
		}else{
			if(s.empty()){
				printf("Invalid\n");
				continue;
			}
			target = (s.size() + 1) / 2;
			lo = 1, hi = 100000;
			while(lo < hi){
				mid = (lo + hi) >> 1;
				curr = get_sum(mid);
				if(curr < target) lo = mid + 1;
				else hi = mid;
			}
			printf("%d\n", lo);
		}
	}
	return 0;
}
