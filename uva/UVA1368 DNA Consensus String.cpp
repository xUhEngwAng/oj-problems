#include <map>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

vector<string> seq;
map<char, int> cnt;

void update(){
	cnt['A'] = 0;
	cnt['G'] = 0;
	cnt['C'] = 0;
	cnt['T'] = 0;
}

char findmax(){
	char res;
	int max = 0;
	for(auto e : cnt)
		if(e.second > max){
			max = e.second;
			res = e.first;
		}
	return res;
}

int main(){
	int N, m, n, err;
	char ch;
	cin >> N;
	string currline, res;
	while(N--){
		cin >> m >> n;
		seq.resize(m);
		for(int ix = 0; ix != m; ++ix){
			cin >> currline;
			seq[ix] = currline;
		}
		res.clear();
		err = 0;
		for(int ix = 0; ix != n; ++ix){
            update();
			for(int jx = 0; jx != m; ++jx)
				cnt[seq[jx][ix]]++;
			ch = findmax();
			res.push_back(ch);
			err += m - cnt[ch];
		}
		cout << res << endl;
		cout << err << endl;
	}
	return 0;
}
