#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
	int N;
	cin >> N;
	vector<int> nums(N), ispivot(N,1), pivot;
	for(auto iter = nums.begin(); iter != nums.end(); iter++){
		cin >> *iter;
	}
	for(int idx = 0; idx != N; idx++){
		if(!ispivot[idx]) continue;
		for(int left = 0; left != idx; left++){
			if(nums[left] > nums[idx]){
				ispivot[idx] = 0;
				break;
			}
		}
		if(!ispivot[idx]) continue;
		for(int right = idx + 1; right != N; right++){
			if(nums[right] < nums[idx]){
				ispivot[idx]   = 0;
				ispivot[right] = 0;
				break;
			}
		}
		if(ispivot[idx]) pivot.push_back(nums[idx]);
	}
	sort(pivot.begin(), pivot.end());
	cout << pivot.size() << endl;
	if(pivot.size()){
		cout << pivot[0];
		for (auto iter = pivot.begin() + 1; iter != pivot.end(); iter++)
			cout << ' ' << *iter;
	}
	return 0;
}
