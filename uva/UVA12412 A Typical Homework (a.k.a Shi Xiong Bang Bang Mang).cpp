#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * 就两个注意事项。其一是在 statistics 中，如果当前班级的人数
 * 为零，则平均分输出 0.00 即可，小心不要除零。
 * 其二是在 ranklist 中，题目上给的是中文的单引号 <’>，这个是
 * 错误的，应该输出英文的单引号 <'>
 */

struct subject{
	int total_score;
	int number_passed;
	int number_failed;
}subj[4];

int overall_passed[5];
char course_name[4][12] = {"Chinese", "Mathematics", "English", "Programming"};

struct student{
	char SID[11], name[11];
	int score[4], CID;
	int rank, total;
};

vector<student> stud;
student tmp;

void printMenu(){
	printf("Welcome to Student Performance Management System (SPMS).\n\n");
	printf("1 - Add\n");
	printf("2 - Remove\n");
	printf("3 - Query\n");
	printf("4 - Show ranking\n");
	printf("5 - Show Statistics\n");
	printf("0 - Exit\n\n");
}

void add(){
	char SID[11], name[11];
	int CID, one, two, three, four;
	bool duplicate;
	while(true){
		printf("Please enter the SID, CID, name and four scores. Enter 0 to finish.\n");
		scanf("%s", SID);
		if(strcmp(SID, "0") == 0) break;
		scanf("%d %s %d %d %d %d", &CID, name, &one, &two, &three, &four);
		duplicate = false;
		for(int ix = 0; ix != stud.size(); ++ix)
			if(strcmp(stud[ix].SID, SID) == 0){
				duplicate = true;
				break;
			}
		if(duplicate){
			printf("Duplicated SID.\n");
			continue;
		}
		strcpy(tmp.SID, SID);
		strcpy(tmp.name, name);
		tmp.CID = CID;
		tmp.score[0] = one;
		tmp.score[1] = two;
		tmp.score[2] = three;
		tmp.score[3] = four;
		tmp.total = one + two + three + four;
		stud.push_back(tmp);
	}
}

void remove(){
	char str[11];
	int number_removed;
	while(true){
		printf("Please enter SID or name. Enter 0 to finish.\n");
		scanf("%s", str);
		if(strcmp(str, "0") == 0) break;
		number_removed = 0;
		for(int ix = 0; ix != stud.size(); ++ix){
			if(strcmp(stud[ix].name, str) == 0 || 
			   strcmp(stud[ix].SID, str) == 0){
				++number_removed;
				stud.erase(stud.begin() + ix);
				--ix;
			}
		}
		printf("%d student(s) removed.\n", number_removed);
	}
}

bool cmp(int one, int two){
	return stud[one].total > stud[two].total;
}

void query(){
	char str[11];
	vector<int> rank;
	for(int ix = 0; ix != stud.size(); ++ix)
			rank.push_back(ix);
	sort(rank.begin(), rank.end(), cmp);
	stud[rank[0]].rank = 1;
	for(int ix = 1; ix != rank.size(); ++ix){
		if(stud[rank[ix]].total == stud[rank[ix - 1]].total)
			stud[rank[ix]].rank = stud[rank[ix - 1]].rank;
		else
			stud[rank[ix]].rank = ix + 1;
	}
	while(true){
		printf("Please enter SID or name. Enter 0 to finish.\n");
		scanf("%s", str);
		if(strcmp(str, "0") == 0) break;
		for(int ix = 0; ix != stud.size(); ++ix){
			if(strcmp(stud[ix].name, str) == 0 || 
			   strcmp(stud[ix].SID, str) == 0)
				printf("%d %s %d %s %d %d %d %d %d %.2f\n", 
					    stud[ix].rank, stud[ix].SID, stud[ix].CID, stud[ix].name, 
					    stud[ix].score[0], stud[ix].score[1], stud[ix].score[2], stud[ix].score[3], 
					    stud[ix].total, (float)stud[ix].total / 4 + 1e-5);
		}
	}
}

void printRank(){
	printf("Showing the ranklist hurts students' self-esteem. Don't do that.\n");
}

void statistics(){
	printf("Please enter class ID, 0 for the whole statistics.\n");
	int CID, cnt = 0, number_passed;
	scanf("%d", &CID);
	memset(subj, 0, sizeof(subj));
	memset(overall_passed, 0, sizeof(overall_passed));
	for(int ix = 0; ix != stud.size(); ++ix){
		if(stud[ix].CID == CID || CID == 0){
			++cnt;
			number_passed = 0;
			for(int jx = 0; jx != 4; ++jx){
				subj[jx].total_score += stud[ix].score[jx];
				if(stud[ix].score[jx] >= 60){
					subj[jx].number_passed++;
					number_passed++;
				}
				else subj[jx].number_failed++;
			}
			overall_passed[number_passed]++;
		}
	}
	for(int ix = 0; ix != 4; ++ix){
		printf("%s\n", course_name[ix]);
		if(cnt) printf("Average Score: %.2f\n", (float)subj[ix].total_score / cnt + 1e-5);
		else printf("Average Score: 0.00\n");
		printf("Number of passed students: %d\n", subj[ix].number_passed);
		printf("Number of failed students: %d\n", subj[ix].number_failed);
		printf("\n");
	}
	printf("Overall:\n");
	printf("Number of students who passed all subjects: %d\n", overall_passed[4]);
	printf("Number of students who passed 3 or more subjects: %d\n", overall_passed[3] + overall_passed[4]);
	printf("Number of students who passed 2 or more subjects: %d\n", overall_passed[2] + overall_passed[3] + overall_passed[4]);
	printf("Number of students who passed 1 or more subjects: %d\n",  overall_passed[1] + overall_passed[2] + overall_passed[3] + overall_passed[4]);
	printf("Number of students who failed all subjects: %d\n", overall_passed[0]);
	printf("\n");
}

int main(){
	freopen("1.out", "w", stdout);
	int item;
	while(true){
		printMenu();
		scanf("%d", &item);
		if(item == 0) break;
		if(item == 1) add();
		else if(item == 2) remove();
		else if(item == 3) query();
		else if(item == 4) printRank();
		else statistics();
	}
	return 0;
}
