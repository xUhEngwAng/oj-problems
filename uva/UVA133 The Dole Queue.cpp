#include <vector>
#include <cstdio>
#include <string>
#include <iostream>
using namespace std;

int main(){
	int N, k, m, pos1, pos2;
	vector<int> q;
	string one, two, res;
	while(true){
		scanf("%d %d %d", &N, &k, &m);
		if(N == 0 && k == 0 && m == 0) break;
		q.resize(N + 1);
		for(int ix = 1; ix <= N; ++ix)
			q[ix] = ix;
		pos1 = 1, pos2 = N;
		while(q.size() > 1){
			pos1 += k - 1;
			while(pos1 >= (int)q.size()) pos1 -= q.size() - 1;
			while(pos1 <= 0) pos1 += q.size() - 1;
            pos2 -= m - 1;
            while(pos2 >= (int)q.size()) pos2 -= q.size() - 1;
			while(pos2 <= 0) pos2 += q.size() - 1;
			if(pos1 == pos2){
				one = to_string(q[pos1]);
				while(one.size() <= 3) one.insert(one.begin(), ' ');
				res += one + ",";
				q.erase(q.begin() + pos1);
				pos2--;
			}
			else{
				one = to_string(q[pos1]);
				two = to_string(q[pos2]);
				while(one.size() <= 3) one.insert(one.begin(), ' ');
				while(two.size() <= 3) two.insert(two.begin(), ' ');
				res += one + two + ",";
				q.erase(q.begin() + pos1);
				if(pos1 < pos2) q.erase(q.begin() + pos2 - 1);
				else q.erase(q.begin() + pos2);
				if(pos1 < pos2) pos2 -= 2;
				else{pos1--, pos2--;}
			}
		}
		cout << res.substr(0, res.size() - 1) << endl;
	}
	return 0;
}
