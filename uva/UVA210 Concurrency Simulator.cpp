#include <string>
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

/*
 * 此题颇为简单，就一个简单模拟而已，但是在这个过程中我也犯了
 * 一些愚蠢的错误，这里简单记录一下，防止以后再犯，还要花时间
 * debug。真正上机考试时也应该避免这类错误。
 *
 * 1. proc 数组没有初始化就直接用于标准输入了。
 * 2. 验证当前指令是否是 print 语句时，直接写了
 *    if(currline.find("print")) 
 *    可是这个函数是返回出现的位置啊，应该判断返回值是否是 -1。
 * 3. 对于多个 test case 的情况，没有清空变量数组。
 * 
 */

struct Process{
	vector<string> statements;
	int curline = 0;
};

vector<Process> proc;
vector<int> variables(26, 0);
vector<int> exectime(5);
deque<int> ready, block;
int currproc, timeExpire, lock = 0;

void exec(){
	int linenum = proc[currproc].curline++;
	string currline = proc[currproc].statements[linenum];
	//cout << "curr statement: " << currline << endl;
	int pos, value;
	if((pos = currline.find('=')) != -1){
		value = stoi(currline.substr(pos + 2));
		variables[currline[0] - 'a'] = value;
		timeExpire += exectime[0];
	}else
	if(currline.find("print") != -1){
		cout << currproc + 1 << ": " << variables[currline[6] - 'a'] << endl;;
		timeExpire += exectime[1];
	}else
	if(currline == "lock"){
		timeExpire += exectime[2];
		if(lock == 1){
            proc[currproc].curline--;
			block.push_back(currproc);
			currproc = ready.front();
			ready.pop_front();
			timeExpire = 0;
		}
		lock = 1;
	}else
	if(currline == "unlock"){
		timeExpire += exectime[3];
		lock = 0;
		if(!block.empty()){
			ready.push_front(block.front());
			block.pop_front();
		}
	}else{
		if(!ready.empty()){
			currproc = ready.front();
			ready.pop_front();
			timeExpire = 0;
		}else currproc = -1;
	}
}

int main(){
    //freopen("uva210.out", "w", stdout);
	int ncases, n, quantum;
	string code;
	cin >> ncases;
	while(ncases--){
		cin >> n;
		proc.resize(n);
        fill(variables.begin(), variables.end(), 0);
		for(int ix = 0; ix != 5; ++ix)
			cin >> exectime[ix];
		cin >> quantum;
		cin.ignore();
		for(int ix = 0; ix != n;){
			getline(cin, code);
			proc[ix].statements.push_back(code);
			if(code == "end") ready.push_back(ix++);
		}
		currproc = ready.front();
		ready.pop_front();
		timeExpire = 0;
		while(true){
            //cout << currproc << " running." << endl;
			exec();
			if(currproc == -1) break;
			if(timeExpire >= quantum){
				ready.push_back(currproc);
				currproc = ready.front();
				ready.pop_front();
				timeExpire = 0;
			}
		}
		if(ncases != 0) cout << endl;
	}
	return 0;
}

/*

1

3 1 1 1 1 1 1
a = 4
print a
lock
b = 9
print b
unlock
print b
end
a = 3
print a
lock
b = 8
print b
unlock
print b
end
b = 5
a = 17
print a
print b
lock
b = 21
print b
unlock
print b
end

*/
