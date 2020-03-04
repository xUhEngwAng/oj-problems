#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/*
 * 这个题真的好变态啊......我想了好久好久，就是想不出一个解，
 * 就差用 dfs 暴力来做了。结果看看柳神的代码，不到20行......
 * 我佛了。
 *
 * 此题的思路乃是，对于两个数字段，定义它们的大小关系为
 *
 * one << two <==> one + two < two + one
 *
 * 其中，右边的 + 表示字符串的连接运算。这样，通过一次排序就
 * 可以得到想要的答案了，证明如下：
 *
 * 首先需要说明我们定义的序 << 满足传递性，即如果 a << b, 
 * b << c ==> a << c。这个证明不那么容易，需要使用字符串比较
 * 的定义，分多种情况进行讨论。这样，对于任意 n 个数字片段
 *
 * S1, S2, ..., Sk, ..., Sn
 *
 * 它们中存在最小的一个片段 Sk，现讨论 Sk 应该处于的位置。
 *
 * 假设在最终的排列中，Sk 没有在首部，则可以通过逐对交换，一
 * 步一步将 Sk 换到首部，由于 Sk 的全局最小性，根据 << 的定
 * 义，每一次交换都会使整个序列的值更小，因此 Sk 必须处于首部。
 * 此后，在对第二小，第三小的片段进行类似讨论，即可得到结论。 
 */

bool cmp(const string &one, const string &two){
    return one + two < two + one;
}

int main(){
	int N;
	cin >> N;
	vector<string> numbers(N);
	string curr;
	for(int ix = 0; ix != N; ++ix)
		cin >> numbers[ix];
	sort(numbers.begin(), numbers.end(), cmp);
	string res;
	for(string str: numbers)
		res += str;
	int pos = 0;
	while(res[pos] == '0') ++pos;
	if(pos == res.size()) cout << "0" << endl;
	else cout << res.substr(pos) << endl;
	return 0;
}
