#include <string>
#include <iostream>
#include <map>
using namespace std;

/*
 * 没想到这个题我居然都一次就通过了，有点佩服我自己！一开始
 * 看到这个题我都懵了，我就寻思这有人能做？不过客观一点，其
 * 实也没有那么难，手写一个整数除法就可以了。
 *
 * 这里的关键在于循环的判断，实际上，只要某次的被除数与此前
 * 出现过的被除数相同，就可以判定出现了循环。因此可以利用一
 * 个 map 将所有出现过的被除数（余数）存储起来，连同其出现
 * 的位置，可以迅速判断循环节的长度。
 *
 * 这个题还有一些细节需要注意。首先循环节只包含小数部分，不
 * 包含整数部分，如题中给出的 300 / 31，循环节就没有包含9，
 * 如果是 30 / 31 循环节就会包含9了。因此可以首先对整数部分
 * 进行处理，令 m = m - (m / n) * n，这样接下来的小数部分
 * 处理起来就相同了。
 *
 * 还需要注意输出格式的问题，这个是题目上没有说清楚的。即在
 * 每个输出之后都要留一个空行，最后一个输出也不例外。
 */

map<int, int> posi;

int main(){
	int m, n, integer, count, tmp;
	string res;
	while(cin >> m >> n){
		cout << m << '/' << n << " = ";
		res.clear();
		integer = m / n;
		m = m - integer * n;
		count = 0;
		posi.clear();
		while(true){
			m *= 10;
			if(posi.find(m) != posi.end()) break;
			posi[m] = count++;
			tmp = m / n;
			res.push_back(tmp + '0');
			m = m - tmp * n;
		}
		cout << integer << '.';
		tmp = posi[m];
		cout << res.substr(0, tmp) << '('
		     << res.substr(tmp, 50 - tmp);
		if(res.size() > 50) cout << "...)" << endl;
		else cout << ')' << endl;
		cout << "   " << count - tmp << " = number of digits in repeating cycle" << endl;
		cout << endl;
	}
	return 0;
}
