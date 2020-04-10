#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <queue>
#include <map>
using namespace std;

/*
 * 这个题的控制逻辑是比较简单的，难点主要在于各种细节比较多，
 * 需要合理选择数据结构，此外按照题目一步一步做就可以了。
 *
 * 我这里选用的数据结构算是比较复杂了，但是相应的性能应该也
 * 比较高。首先对于每一个 mta 都唯一分配了一个id，因此分别
 * 用一个 map 和 vector 来存储互相转换的映射。每一个 mta 所
 * 含有的用户则用一个 set 来存储，所有用户就组织成了 vector<set>
 * 
 * 还有一个问题是如何按照 mta 顺序把所有收件人组织起来，这有点
 * 类似与前面 Team Queue (uva540) 这个题，我因此采用了同样的
 * 策略，使用一个全局队列来保存每一个 mta，而每一个 mta 都管理
 * 着自己的一个队列，这两个结构分别是 mta_queue 以及 q。
 *
 * 此外，有一个细节问题需要注意，题目上说了收件人是没有重复的，
 * 然而在数据中是存在这样的输入的。
 */

map<string, int> mta_hash;
vector<string> unmap_mta, data;
vector<set<string>> mta_info;
queue<int> mta_queue;
vector<queue<string>> q;

int main(){
	//freopen("1.out", "w", stdout);
	string str;
	int num, cnt = 0;
	while(true){
		cin >> str;
		if(str[0] == '*') break;
		cin >> str;
		mta_hash[str] = cnt++;
		unmap_mta.push_back(str);
		mta_info.push_back(set<string>());
		cin >> num;
		while(num--){
			cin >> str;
			mta_info.back().insert(str);
		}
	}
	q.resize(cnt);
	int pos, mta_id;
	string sender, recer, send_mta, rece_mta;
	set<string> recipient;
	while(true){
		cin >> sender;
		if(sender[0] == '*') break;
		send_mta = sender.substr(sender.find('@') + 1);
		recipient.clear();
		while(true){
			cin >> recer;
			if(recer[0] == '*') break;
			if(recipient.find(recer) != recipient.end()) continue;
			recipient.insert(recer);
			pos = recer.find('@');
			rece_mta = recer.substr(pos + 1);
			recer = recer.substr(0, pos);
			mta_id = mta_hash[rece_mta];
			if(q[mta_id].empty()) mta_queue.push(mta_id);
			q[mta_id].push(recer);
		}
		data.clear();
		cin.ignore();
		while(true){
			getline(cin, str);
			if(str[0] == '*') break;
			data.push_back(str);
		}
		while(!mta_queue.empty()){
			mta_id = mta_queue.front();
			rece_mta = unmap_mta[mta_id];
			cout << "Connection between " << send_mta << " and " << rece_mta << endl;
			cout << "     HELO " << send_mta << endl;
			cout << "     250" << endl;
			cout << "     MAIL FROM:<" << sender << '>' << endl;
			cout << "     250" << endl;
			cnt = 0;
			while(!q[mta_id].empty()){
				recer = q[mta_id].front();
				q[mta_id].pop();
				cout << "     RCPT TO:<" << recer << '@' << rece_mta << '>' << endl;
				if(mta_info[mta_id].find(recer) != mta_info[mta_id].end()){
					cout << "     250" << endl;
					++cnt;
				}
				else cout << "     550" << endl;
			}
			if(cnt != 0){
				cout << "     DATA" << endl;
				cout << "     354" << endl;
				for(string s: data)
					cout << "     " << s << endl;
				cout << "     ." << endl;
				cout << "     250" << endl;
			}
			cout << "     QUIT" << endl;
			cout << "     221" << endl;
			mta_queue.pop();
		}
	}
	return 0;
}
