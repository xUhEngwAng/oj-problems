#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<vector<string>> database;

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
		for(int ix = 0; ix < n; ++ix)
			for(int jx = ix + 1; jx < n; ++jx){
				cnt = 0;
				for(int kx = 0; kx != m; ++kx)
					if(database[ix][kx] == database[jx][kx])
						++cnt;
				if(cnt >= 2){
					row1 = ix, row2 = jx;
					goto out;
				}
			}
		out:
		if(cnt < 2) printf("YES\n");
		else{
			cnt = 0;
			printf("NO\n");
			printf("%d %d\n", row1 + 1, row2 + 1);
			for(int ix = 0; ix != m; ++ix)
				if(database[row1][ix] == database[row2][ix]){
					++cnt;
					if(cnt == 1) col1 = ix;
					if(cnt == 2) col2 = ix;
				}
			printf("%d %d\n", col1 + 1, col2 + 1);
		}	
	}
	return 0;
}
