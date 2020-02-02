#include <vector>
#include <cstdio>
#include <cstdlib>
using namespace std;

/*
 * 这个题感觉非常有难度啊，不愧是30分的题！一开始看到这个题
 * 我就知道应该用**试探回溯法**来做，无奈还是做了很久，因为
 * 确实从来没有写过试探回溯的代码，非常不熟练，一开始甚至没
 * 有想到使用 stack ......
 * 然后我好好回顾了八皇后问题，才终于想出一种可行解法：
 * 
 * 1. 引入一个栈来存储每一位选择的数字，为了防止重复组合出现，
 *    栈的元素是增序排列的。
 * 2. 每一次迭代试探下一位的数字，记为 curr，应该满足
 *    curr >= stack.top()。添加该数字入栈后，检查当前序列是
 *    否可能出现，即 P 幂方和是否小于 N。若否，则向前回溯，即
 *    首先弹出 curr，再令当前的栈顶加一。
 * 3. 若当前序列合法，且栈的规模等于 K，说明已经获得了一个完整
 *    的组合，检查 P 幂方和是否等于 N，若等于，则将当前组合保
 *    存到一个向量中，以供后续选取；然后向前回溯，找出其他可能
 *    的组合。若不等于，直接向前回溯即可。重复2、3步的操作，直至
 *    某次需要弹栈时栈空，说明所有可能情况已经遍历完毕。
 * 4. 检查所有得到的组合，选出符合题目要求的即可。
 *
 * 在实现过程中还遇到了一些问题，比如一开始求幂方是使用库函数
 * power，无奈该函数的参数是 double 类型的，会出现精度不足的
 * 问题，只好自己写整数的 power，还好好回顾了 O(logn) 的递归
 * 和非递归的 power 函数的写法。
 *
 * 看《算法笔记》的解法，是用 dfs 做的，写起来感觉要简单很多，不
 * 过我觉得中间的思路也不简单。总的来说，两个方法的本质是一样的，
 * 试探回溯法本来就等价于深度优先搜索，我的代码应该更高效一点，
 * 毕竟是非递归的。
 */

int pow(int base, int radix){
    int res = 1, pow = base;
    while(radix){
        if(radix & 1) res *= pow;
        pow = pow * pow;
        radix = radix >> 1;
    }
    return res;
}

int power_sum(const vector<int> &input, int radix){
	int res = 0;
	for(int e : input)
		res += pow(e, radix);
	return res;
}

bool ifPossible(const vector<int> &input, int radix, int K, int N){
	int res = power_sum(input, radix);
	if(input.size() < K)
		res += pow(input.back(), radix) * (K - input.size());
	return res <= N;
}

int sum(const vector<int> &input){
	int res = 0;
	for(int e : input)
		res += e;
	return res;
}

bool gt(const vector<int> &left, const vector<int> &right){
	int ix = left.size() - 1;
	while(left[ix] == right[ix]) --ix;
	return left[ix] > right[ix];
}

int main(){
	int N, K, P;
	scanf("%d %d %d", &N, &K, &P);
	vector<int> stack;
	vector<vector<int>> res;
	stack.reserve(K);

	int curr = 1;
	while(true){
		stack.push_back(curr);
		if(!ifPossible(stack, P, K, N)){
			stack.pop_back();
			if(stack.empty()) break;
			curr = stack.back() + 1;
			stack.pop_back();
		}
		else{
			if(stack.size() == K){
				if(power_sum(stack, P) == N){
					res.push_back(stack);
					stack.pop_back();
					if(stack.empty()) break;
					curr = stack.back() + 1;
					stack.pop_back();
				}
				else{
					stack.pop_back();
					curr++;
				}
			}
		}
	}

	if(res.size() == 0) printf("Impossible\n");
	else{
		int maxSum = 0, currSum;
		vector<vector<int>>::const_iterator max;
		for(auto it = res.cbegin(); it != res.cend(); ++it){
			currSum = sum(*it);
			if(currSum > maxSum){
				maxSum = currSum;
				max = it;
			}else
			if(currSum == maxSum)
				if(gt(*it, *max)) max = it;
		}
		printf("%d = %d^%d", N, max->back(), P);
		for(int ix = max->size() - 2; ix >= 0; --ix)
			printf(" + %d^%d", max->at(ix), P);
	}
	return 0;
}
