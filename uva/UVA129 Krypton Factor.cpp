#include <cstdio>
#include <string>
using namespace std;

/*
 * 这个题的基本算法是试探回溯法，本来我觉得我已经对这种方法
 * 非常熟悉了，结果编码的过程中还是出现了不少错误，这里总结
 * 一下。
 *
 * 首先说明一下整体算法，这里是增量构造算法来构造串，即从前一
 * 个困难串出发，在其后增加一个字符，判断这个新串是否仍是一个
 * 困难串，只需要检查新串的所有后缀即可。
 *
 * 然后这里的试探回溯是不同于传统的情形，这里只需要进行 n 次，
 * 就要及时刹车，因此我这里的处理不太成熟。看紫书上面的解法，
 * 是通过返回值来刹车的，可以参考借鉴。
 *
 * 这里还犯了一个常犯的错误，当 container.size() 放在判断中
 * 时，要特别小心它的值为负，由于其类型是 unsigned，一旦为负
 * 就变成了 int 型的超级大数了。
 */

int n, l;
string str;

bool isvalid(int num){
	int one, two;
	bool res = true;
	str.push_back(num + 'A');
	for(int ix = str.size() - 2; ix >= (int)(str.size() - 1) / 2; --ix){
		one = str.size() - 1;
		two = ix;
		while(one > ix && str[one] == str[two]) {--one, --two;}
		if(one == ix){
			res = false;
			break;
		}
	}
	str.pop_back();
	return res;
}

void dfs(int curr, int &cnt){
	str.push_back(curr + 'A');
	cnt++;
	if(cnt == n) return;
	for(int ix = 0; ix != l; ++ix){
		if(isvalid(ix))
			dfs(ix, cnt);
		if(cnt == n) return;
	}
	str.pop_back();
}

int main(){
	//freopen("1.out", "w", stdout);
	int cnt, num;
	while(scanf("%d %d", &n, &l) == 2){
		if(n == 0) break;
		str.clear();
		cnt = 0;
		for(int ix = 0; ix != l; ++ix){
			dfs(ix, cnt);
			if(cnt == n) break;
		}
		cnt = num = 0;
		for(int ix = 0; ix != str.size(); ++ix){
			printf("%c", str[ix]);
			if(++cnt == 4 && ix != str.size() - 1){
				if(++num == 16){
					printf("\n");
					num = 0;
				}
				else printf(" ");
				cnt = 0;
			}
		}
		printf("\n%d\n", str.size());
	}
	return 0;
}
