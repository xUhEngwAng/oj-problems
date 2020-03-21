#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

/*
 * 这个题没想到也是颇费了一番周折，本来的代码就是直接暴力枚举，
 * （因为我也想不出其他更优的方法了......），意料之中地超时了。
 *
 * 更优的算法是对列进行枚举，对于每两列，再枚举所有的行，将这
 * 两列的值存储到一个 map 当中。如果在某一行发现当前值已经在
 * map 中出现过，就说明不满足 PNF 范式。该算法的时间复杂度为
 * O(m^2 x nlogn)，比我的 O(n^2 x m) 好了不少。
 *
 * 上面的算法还可以进行进一步的优化，比如将一开始输入的所有串
 * 都赋予一个唯一的编号，在表中只用存储这些编号即可，就可以避免
 * 后续 map 中操作字符串比较带来的开销。
 */

vector<vector<string>> database;
map<string, int> entry;

void parse(const string &str, int rownum){
	int begin = 0, next;
	while(true){
		next = str.find(',', begin);
		if(next == -1) break;
		database[rownum].push_back(str.substr(begin, next - begin));
		begin = next + 1;
	}
	database[rownum].push_back(str.substr(begin));
}

int main(){
	freopen("1.out", "w", stdout);
	int m, n, cnt;
	int row1, row2, col1, col2;
	bool flag;
	string str;
	while(cin >> n >> m){
		cin.ignore();
		database.clear();
		database.resize(n);
		for(int ix = 0; ix != n; ++ix){
			getline(cin, str);
			parse(str, ix);
			/*
			for(string s : database[ix])
				cout << s << ' ';
			cout << endl;*/
		}
		for(int ix = 0; ix < m; ++ix)
			for(int jx = ix + 1; jx < m; ++jx){
				entry.clear();
				flag = false;
				for(int kx = 0; kx != n; ++kx){
					str = database[kx][ix] + ',' + database[kx][jx];
					if(entry.find(str) == entry.end())
						entry[str] = kx;
					else{
						row1 = entry[str], row2 = kx;
						col1 = ix, col2 = jx;
						flag = true;
						goto out;
					}
				}
			}
		out:
		if(flag)
			printf("NO\n%d %d\n%d %d\n", row1 + 1, row2 + 1, col1 + 1, col2 + 1);
		else
			printf("YES\n");
	}
	return 0;
}
