#include <set>
#include <cstdio>
using namespace std;

struct Point{
	int xpos;
	int ypos;
	Point() = default;
	Point(int x, int y): xpos(x), ypos(y){}
	bool operator<(const Point &right) const {
	    if(xpos == right.xpos) return ypos < right.ypos;
        return xpos < right.xpos;
	}
};

set<Point> graph;

bool isvalid(int x, int y){
	Point tmp(x + 1, y);
	if(graph.find(tmp) == graph.end()) return false;
	tmp.xpos -= 2;
	if(graph.find(tmp) == graph.end()) return false;
	tmp.xpos = x;
	tmp.ypos = y + 1;
	if(graph.find(tmp) == graph.end()) return false;
	tmp.ypos -= 2;
	if(graph.find(tmp) == graph.end()) return false;
	return true;
}

int countScore(int x, int y){
	int res = 0;
	Point tmp(x + 1, y + 1);
	if(graph.find(tmp) != graph.end()) ++res;
	tmp.xpos -= 2;
	if(graph.find(tmp) != graph.end()) ++res;
	tmp.ypos -= 2;
	if(graph.find(tmp) != graph.end()) ++res;
	tmp.xpos += 2;
	if(graph.find(tmp) != graph.end()) ++res;
	return res;
}

int main(){
    //freopen("201912-2-1.in", "w", stdin);
	int N, x, y, score;
	scanf("%d", &N);
	for(int ix = 0; ix != N; ++ix){
		scanf("%d %d", &x, &y);
		graph.insert(Point(x, y));
	}
	int res[5] = {0, 0, 0, 0, 0};
	for(auto it = graph.begin(); it != graph.end(); ++it){
		if(!isvalid(it->xpos, it->ypos)) continue;
		score = countScore(it->xpos, it->ypos);
		res[score]++;
	}
	for(int ix = 0; ix != 5; ++ix)
		printf("%d\n", res[ix]);
	return 0;
}
