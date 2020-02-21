#include <vector>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

/*
 * 这个题相当有意思。我先说一下我的整体思路。
 *
 * 简单说来就是暴力解法：逐个枚举撒谎的两个人，就可以得到 N 个
 * 关于身份的正确论断。首先判断这些论断是否有相互矛盾，如果有则
 * 重新枚举新的两个人。如果没有相互矛盾还需要做进一步的判断，首
 * 先是对两个撒谎的人的身份，必然是一个好人一个坏人；此外还可能
 * 有一些的身份仍然是未确定的，需要结合已经确定的狼人数量做额外
 * 的判断。
 *
 * 这里需要注意多于一个解的情形，设想一种情况，目前只确定了一个
 * 狼人，而有三个人的身份未定，此时该狼人与这三个人中的一个任意
 * 组合都是一组解，按照题目的要求应该选出其中最小的那个。而我一
 * 开始的策略则是把这种情况当做无解来看待，因此有一个测试点没有
 * 通过。
 *
 * 再设想一种情形，两个撒谎者 i, j 的身份都是未确定的，我之前直
 * 把这种情况当做无解。按照上面的思想，为了挑选出最小的解，应该把
 * i, j 中更小的那个视作坏人，更大的那个视作好人。
 *
 * 这样就可以得到整体的判断思路了：如果确实没有发生论断的矛盾，
 * 则首先确定两个撒谎者的身份，如果两者身份相同，则与前提条件不
 * 同，故直接返回。确定了两者的身份后，对所有人进行一次遍历，找
 * 到其中的所有狼人，如果数量大于3，则显然不对；如果数量为2，则
 * 就是我们要的一组解；如果数量为1，则再次遍历，找到第一个身份
 * 未定的人，将他标记为狼人即可。狼人的数量不可能为零，因为两个
 * 撒谎者中会确定一个狼人。
 */

struct node{
	int one;
	int two;
	node() = default;
	node(int one, int two): one(one), two(two){}
	bool operator<(const node &right){
		if(one != right.one)
			return one < right.one;
		return two < right.two;
	}
};

int main(){
	int N;
	scanf("%d", &N);
	int *arr = new int[N + 1], id;
	for(int ix = 1; ix <= N; ++ix)
		scanf("%d", arr + ix);
	vector<int> identity(N + 1);
	vector<int> tmp;
	vector<node> res;
	for(int ix = 1; ix < N; ++ix)
		for(int jx = ix + 1, kx; jx <= N; ++jx){
            tmp.clear();
            fill(identity.begin(), identity.end(), 0);
			for(kx = 1; kx <= N; ++kx){
				if(arr[kx] < 0) id = -1;
				else            id = 1;
				if(kx == ix || kx == jx){
					if(identity[abs(arr[kx])] == id)
						break;
					identity[abs(arr[kx])] = -id;
				}
				else{
					if(identity[abs(arr[kx])] == -id)
						break;
					identity[abs(arr[kx])] = id;
				}
			}
			if(kx < N + 1) continue;
			if(identity[ix] * identity[jx] == 1) continue;
			if(identity[ix] == 0 && identity[jx] == 0){
				identity[ix] = -1;
				identity[jx] = 1;
			}
			if(identity[ix] == 0) identity[ix] = -identity[jx];
            if(identity[jx] == 0) identity[jx] == -identity[ix];
            for(kx = 1; kx <= N; ++kx)
                if(identity[kx] == -1)
                    tmp.push_back(kx);
            if(tmp.size() > 2) continue;
            if(tmp.size() == 2) res.emplace_back(tmp[0], tmp[1]);
			else{
                for(kx = 1; kx <= N; ++kx)
                    if(identity[kx] == 0){
                        tmp.push_back(kx);
                        break;
                    }
                if(tmp.size() != 2) continue;
                sort(tmp.begin(), tmp.end());
                res.emplace_back(tmp[0], tmp[1]);
			}
		}
	if(res.empty()) printf("No Solution\n");
	else{
		sort(res.begin(), res.end());
		printf("%d %d\n", res.front().one, res.front().two);
	}
	return 0;
}
