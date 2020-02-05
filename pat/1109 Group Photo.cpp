#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

struct person{
	string name;
	int height;

	person() = default;
	person(string n, int h): name(n), height(h){}

	bool operator<(const person& right){
		if(height == right.height)
			return name < right.name;
		return height > right.height;
	}
};

int main(){
	int N, K, height;
	cin >> N >> K;
	vector<person> group;
	string name;
	for(int ix = 0; ix != N; ++ix){
		cin >> name >> height;
		group.emplace_back(name, height);
	}

	sort(group.begin(), group.end());

	int num = N / K, begin = 0, curr, mid, jx;
	vector<vector<int>> res(K);
	res[0] = vector<int>(N - num * (K - 1));
	for(int ix = 1; ix != K; ++ix)
		res[ix] = vector<int>(num);

	for(int ix = 0; ix != K; ++ix){
		curr = res[ix].size();
		mid = (curr >> 1);
		res[ix][mid] = begin++;
		for(jx = 1; jx <= (curr >> 1); ++jx){
			res[ix][mid - jx] = begin++;
			if(begin - res[ix][mid] < curr)
                res[ix][mid + jx] = begin++;
		}
	}

	for(auto v : res){
		cout << group[v[0]].name;
		for(int ix = 1; ix != v.size(); ++ix)
			cout << ' ' << group[v[ix]].name;
		cout << endl;
	}
	return 0;
}
