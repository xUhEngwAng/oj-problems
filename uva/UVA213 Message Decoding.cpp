#include <string>
#include <vector>
#include <iostream>
using namespace std;

/*
 * 通过这个题可以明显地感觉到竞赛题和PAT的差距。其实
 * 这个题本身也比较简单，但是其中的环节就比较复杂，
 * 有很多细节问题需要处理。我看紫书上面给出的解答应该
 * 是比我的繁琐，但是它的结构非常好，值得我学习。就是
 * 首先给出了程序的整体框架，然后再逐步填补细节。
 *
 * 这里还有一个关于输入的细节需要注意，对于头部的输入，
 * 我是使用一个 getline 来实现的。但是上一轮结束时输入
 * 的回车符会影响这里的 getline，因此需要将该回车符忽
 * 略，这是通过 cin.ignore 来实现的。
 *
 * cin.ignore(cnt, char) 从输入流中提取字符，然后将
 * 该字符忽略，直到忽略的字符数量达到 cnt，或者提取的
 * 字符 = char。如果不带参数，则等价于 cin.ignore(1, EOF)
 *
 * 此外还有 stoi 的参数问题。 stoi(str, p, b) 中 p 
 * 表示从第 p 个位置开始进行字符串到整数的转换；b 表示
 * 转换采用的进制数。我在一开始是忽略了 p 这个参数。
 */

int start[8] = {0, 0, 1, 4, 11, 26, 57, 120};

bool isTerminate(const string &str){
	for(char ch : str)
		if(ch != '1')
			return false;
	return true;
}

int main(){
	string header, content, tmp, res;
	int len, pos;
	vector<char> coder;
	while(true){
        getline(cin, header);
        if(!cin) break;
		coder.assign(header.begin(), header.end());
		cin >> content;
		pos = 0;
		while(true){
			while(pos + 3 > content.size()){
				cin >> tmp;
				content += tmp;
			}
			len = stoi(content.substr(pos, 3), 0, 2);
			if(len == 0) break;
			pos += 3;
			while(true){
				while(pos + len > content.size()){
					cin >> tmp;
					content += tmp;
				}
				tmp = content.substr(pos, len);
				pos += len;
				if(isTerminate(tmp)) break;
				res += coder[stoi(tmp, 0, 2) + start[len]];
			}
		}
		cout << res << endl;
        cin.ignore(1024, '\n');
        res.clear();
	}
	return 0;
}
