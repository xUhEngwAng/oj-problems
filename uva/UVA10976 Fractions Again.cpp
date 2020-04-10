#include <cstdio>
#include <vector>
using namespace std;

/*
 * 这种水题我第一次交居然还超时了？？？检查了一下我的代码，循环
 * 退出部分我是下面这样写的：
 *
 * if(up % down == 0)
 *     x = up / down
 *     if(x < y) break;
 *     ......
 *
 * 即只在判定了整除的条件下才判断 x, y 的相对大小。设想某次 x==y
 * 则需要等到下一次整除才能退出循环。这还不是最糟，好歹可以退出
 * 啊，设想输入 k = 1，则过了 y = 2 这村就没有退出这店了，陷入
 * 了死循环。实际上，检查到 x==y 就退出才是最好的。
 */

struct triple{
	int x, y, k;
	triple() = default;
	triple(int x, int y, int k): x(x), y(y), k(k){}
};

vector<triple> res;

int main(){
	int k, x, y, cnt;
	int up, down;
	while(scanf("%d", &k) == 1){
		cnt = 0;
		res.clear();
		y = k + 1;
		while(true){
			up = y * k;
			down = y - k;
			if(up % down == 0){
				x = up / down;
				++cnt;
				res.emplace_back(x, y, k);
				if(x == y) break;
			}
			++y;
		}
		printf("%d\n", cnt);
		for(auto e : res)
			printf("1/%d = 1/%d + 1/%d\n", e.k, e.x, e.y);
	}
	return 0;
}
