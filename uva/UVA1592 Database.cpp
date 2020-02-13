#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

string database[10000][10];

int check_row(int row1, int row2, int colSrc, int m){
	while(colSrc < m){
		if(database[row1][colSrc] == database[row2][colSrc])
			return colSrc;
		colSrc++;
	}
	return -1;
}

int main(){
	int m, n, pos, prev;
	int row1, row2, col1, col2;
	bool flag;
	string currline;
	map<string, vector<int>> mp;
	map<string, vector<int>>::iterator it;
	while(cin >> n >> m){
		flag = true;
		cin.ignore();
		for(int jx = 0; jx < n; ++jx){
			getline(cin, currline);
			prev = 0, pos = 0;
			for(int ix = 0; ix < m - 1; ++ix){
				pos = currline.find(',', prev);
				database[jx][ix] = currline.substr(prev, pos - prev);
				cout << database[jx][ix] << " ";
				prev = pos + 1;
			}
			database[jx][m - 1] = currline.substr(prev);
			cout << database[jx][m - 1];
			cout << endl;
		}
		for(int ix = 0; ix < m - 1; ++ix){
			mp.clear();
			for(int jx = 0; jx != n; ++jx)
				if((it = mp.find(database[jx][ix])) == mp.end())
					mp[database[jx][ix]].push_back(jx);
				else
					it->second.push_back(jx);
			for(auto p : mp){
				if(p.second.size() == 1) continue;
				for(int kx = 0; kx != p.second.size(); kx++)
					for(int lx = kx + 1;lx != p.second.size(); lx++)
						if((col2 = check_row(p.second[kx], p.second[lx], ix + 1, m)) != -1){
							flag = false;
							row1 = p.second[kx];
							row2 = p.second[lx];
							col1 = ix;
							goto out;
						}
			}
		}
		out:
		if (flag) cout << "YES" << endl;
		else {
			cout << "NO" << endl;
			cout << row1 + 1 << " " << row2 + 1 << endl;
			cout << col1 + 1 << " " << col2 + 1 << endl;
		}
	}
	system("pause");
	return 0;
}
