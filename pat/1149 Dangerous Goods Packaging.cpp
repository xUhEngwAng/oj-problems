#include <vector>
#include <cstdio>
using namespace std;

/*
 * 这里有一个问题需要说明一下。有一个循环，我的终止条件是
 *
 * ix < seq.size() - 1
 *
 * 但是要注意的是，seq.size() 的返回值是 unsigned int，
 * 如果 seq.size() == 0，那么 seq.size() - 1 就会是
 * unsigned int 可以表示的最大的数字，大约是 0xffffffff。
 * 为了避免这个问题，需要进行强制类型转化，即写成
 *
 * ix < (int)seq.size() - 1
 */

vector<vector<bool>> matrix(20000, vector<bool>(20000));
vector<int> map(100000, -1);

int main(){
	int N, M, one, two, count = 0;
	scanf("%d %d", &N, &M);
	for(int ix = 0; ix != N; ++ix){
		scanf("%d %d", &one, &two);
		if(map[one] == -1) map[one] = count++;
		if(map[two] == -1) map[two] = count++;
		matrix[map[one]][map[two]] = true;
		matrix[map[two]][map[one]] = true;
	}
	int num;
	bool flag;
	vector<int> seq;
	seq.reserve(1000);
	while(M--){
		flag = true;
		scanf("%d", &num);
		while(num--){
			scanf("%d", &one);
			if(map[one] == -1) continue;
			seq.push_back(map[one]);
		}
		for(int ix = 0; ix < (int)seq.size() - 1; ++ix){
			for(int jx = ix + 1; jx < seq.size(); ++jx)
				if(matrix[seq[ix]][seq[jx]]){
					flag = false;
					break;
				}
			if(!flag) break;
		}
		if(flag) printf("Yes\n");
		else     printf("No\n");
		seq.clear();
	}
	return 0;
}
