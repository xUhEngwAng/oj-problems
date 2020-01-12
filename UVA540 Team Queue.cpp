#include <cstdio>
#include <list>
#include <map>

#define MAXTEAM 1000

using namespace std;

struct member{
	int id;
	int nteam;

	member(int id, int team_num): id(id), nteam(team_num){}
};

struct team{
	int count;                              //number of elements in q
	list<member*>::iterator pos;            //position of last element in q

	team(): count(0){}
};

int main(){
	int t, num, id, currteam;
	char op[8];

	list<member*> q;
	map<int, int> m;
	team team_info[MAXTEAM];

	while(true){
		scanf("%d", &t);
		if(t == 0) break;
		for(int ix = 0; ix != t; ++ix){
			scanf("%d", &num);
			while(num--){
				scanf("%d", &id);
				m[id] = ix;
			}
		}
		while(true){
			scanf("%s", op);
			if(op[0] == 'E'){//enqueue
				scanf("%d", &id);
				currteam = m[id];
				if(team_info[currteam].count == 0){
					q.push_back(new member(id, currteam));
					team_info[currteam].pos = q.;
				}
				else{
					q.insert(team_info[currteam].pos, new member(id, currteam));
					team_info[currteam].pos = team_info[currteam].pos.;
				}
				team_info[currteam].count++;
			}
			else if(op[0] == 'D'){
				q.pop_front();
			}
		}
		m.clear();
		q.clear();
	}
}
