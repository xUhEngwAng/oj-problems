#include <stdio.h>
#include <map>
#include <set>
using namespace std;
int main(){
	int N, K;
	scanf("%d %d", &N, &K);
	map<string, set<int>> courses;
	int courseid, num;
	char stu[5];
	for(int ix = 0; ix != K; ix++){
		scanf("%d %d", &courseid, &num);
		while(num--){
			scanf("%s", stu);
			courses[stu].insert(courseid);
		}
	}
	for(int ix = 0; ix != N; ix++){
		scanf("%s", stu);
		printf("%s", stu);
		printf(" %d", courses[stu].size());
		if(!courses[stu].empty()){
			for (auto It = courses[stu].begin(); It != courses[stu].end(); It++)
				printf(" %d", *It);
		}
		printf("\n");
	}
	system("pause");
	return 0;
}