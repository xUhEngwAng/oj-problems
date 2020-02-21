#include <vector>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

/*
 * 这个题稍显变态。我的思路就是最暴力的思路：用一个邻接矩阵来
 * 存储所有的朋友信息。对于任意的 A 和 B，分别遍历他们的所有
 * 朋友，然后判断这些朋友之间是否有联系，对于每一个 query
 * 的时间复杂度是 O(N^2)。
 *
 * 在这个过程中要注意一些问题。首先是考虑 A 和 B 同性且本来
 * 就是朋友的情况。此时遍历 A 的朋友时要避免找到了 B；同理
 * 遍历 B 的朋友时要避免找到了 A。
 *
 * 此外还有一个问题是我没有注意到的，首先输出的格式要是 "%04d"
 * 来解决 0 打头的情况。此外还有一个变态输入，是某个人的 id 是
 * 0000 或者 -0000，对于这种情况，我原来的代码时无法分辨的，
 * 因为原来我是通过两个人 id 的乘积的正负号来判断两人是否性别
 * 相异。此时我是通过引入一个 gender 成员来进行判断。
 */

int stoi(char* str, int n){
    int res = 0;
    for(int ix = 0; ix != n; ++ix){
        res = res * 10;
        res += str[ix] - '0';
    }
    return res;
}

struct res_pair{
	int first;
	int second;
	res_pair() = default;
	res_pair(int one, int two): first(one), second(two){}

	bool operator<(const res_pair& right){
		if(first != right.first)
			return first < right.first;
		return second < right.second;
	}
};

struct person{
    int id;
    int gender;
};

int main(){
	int N, M, count;
	scanf("%d %d", &N, &M);
	vector<int> map(10000, -1);
	vector<person> unmap(N);
	vector<vector<bool>> graph(N, vector<bool>(N));
	count = 0;
	char one[6], two[6];
	int left, right, gender1, gender2;
	for(int ix = 0; ix != M; ++ix){
		scanf("%s %s", one, two);
		if(one[0] == '-'){
            gender1 = -1;
            left = stoi(one + 1, 4);
		}else{
            gender1 = 1;
            left = stoi(one, 4);
		}
		if(two[0] == '-'){
            gender2 = -1;
            right = stoi(two + 1, 4);
		}else{
            gender2 = 1;
            right = stoi(two, 4);
		}
		if(map[left] == -1){
			map[left] = count;
			unmap[count].id = left;
			unmap[count].gender = gender1;
			++count;
		}
		if(map[right] == -1){
			map[right] = count;
			unmap[count].id = right;
			unmap[count].gender = gender2;
			++count;
		}
		graph[map[left]][map[right]] = true;
		graph[map[right]][map[left]] = true;
	}
	int K, a, b;
	scanf("%d", &K);
	vector<res_pair> res;
	while(K--){
		scanf("%d %d", &a, &b);
		a = abs(a);
		b = abs(b);
        if(map[a] == -1 || map[b] == -1){
            printf("0\n");
            continue;
        }
        left = map[a];
        right = map[b];
        gender1 = unmap[left].gender;
        gender2 = unmap[right].gender;
		for(int ix = 0; ix != N; ++ix){
			if(graph[left][ix] && ix != right &&
			   gender1 * unmap[ix].gender > 0)
				for(int jx = 0; jx != N; ++jx)
					if(graph[right][jx] && jx != left &&
			   		   gender2 * unmap[jx].gender > 0)
						if(graph[ix][jx])
							res.emplace_back(unmap[ix].id, unmap[jx].id);
		}
		sort(res.begin(), res.end());
		printf("%d\n", res.size());
		for(auto e : res)
			printf("%04d %04d\n", e.first, e.second);
        res.clear();
	}
	return 0;
}
