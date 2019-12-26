#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct stuInfo{
	string stuId;
	short Cmark;
	short Mmark;
	short Emark;
	float aver;
};
vector<stuInfo>::iterator findId(vector<stuInfo> allstu, string srcId);
int main(){
	int stuNum, checkNum;
	cin >> stuNum >> checkNum;
	vector<stuInfo> allstu(stuNum);
	vector<short> cGrade, mGrade, eGrade;
	vector<float> avers;
	vector<stuInfo>::iterator stuIter;
	for(stuIter=allstu.begin();stuIter!=allstu.end();stuIter++){
		cin >> 	stuIter->stuId >> stuIter->Cmark >> stuIter->Mmark >> stuIter->Emark;
		stuIter->aver = (stuIter->Cmark + stuIter->Mmark + stuIter->Emark)/3.;

		cGrade.push_back(stuIter->Cmark);
		mGrade.push_back(stuIter->Mmark);
		eGrade.push_back(stuIter->Emark);
		avers.push_back(stuIter->aver);
	}
	sort(cGrade.begin(), cGrade.end());
	sort(mGrade.begin(), mGrade.end());
	sort(eGrade.begin(), eGrade.end());
	sort(avers.begin(), avers.end());

	string checkId;
	vector<stuInfo>::iterator checkStu;
	int bestRank;
	char bestCourse;
	for(int ix = 0; ix != checkNum; ix++){
		cin >> checkId;
		checkStu = findId(allstu, checkId);
		if(checkStu == allstu.end()) cout << "N/A" <<endl;
		else{
			//check average score

		}
	}
	return 0;
}

vector<stuInfo>::iterator findId(vector<stuInfo> allstu, string srcId){
	vector<stuInfo>::iterator stuIter;
	for(stuIter = allstu.begin(); stuIter != allstu.end(); stuIter++){
		if(srcId == stuIter->stuId) return stuIter;
	}
	return allstu.end();
}

int findPos(vector<short> srcVec, int val){
	int mid, left = 0, right = srcVec.size()-1;
	while(left < right){
		mid = (left + right)/2;
		if(val > srcVec[mid]) left = mid;
		else if(val < srcVec[mid]) right = mid;
		else return 
	}
}