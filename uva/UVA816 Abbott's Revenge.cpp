#include <string>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define INF (0x7fffffff)

struct node{
	string north;
	string south;
	string east;
	string west;
};

struct point{
	int row;
	int col;
	point() = default;
	point(int x, int y): row(x), col(y){}
};

node maze[10][10];
vector<point> path, tmp;
int srcrow, srccol, destrow, destcol;
int minlenth = INF;

string getDir(const string &str){
	string res;
	char dir = str[0];
	for(int ix = 1; ix != str.size(); ++ix){
		if(str[ix] == 'F') res.push_back(dir);
		else if(str[ix] == 'L'){
			if(dir == 'N') res.push_back('W');
			else if(dir == 'S') res.push_back('E');
			else if(dir == 'E') res.push_back('N');
			else res.push_back('S');
		}
		else{
			if(dir == 'N') res.push_back('E');
			else if(dir == 'S') res.push_back('W');
			else if(dir == 'E') res.push_back('S');
			else res.push_back('N');
		}
	}
	return res;
}

void dfs(int row, int col, char dir){
	tmp.emplace_back(row, col);
	//cout << row << ' ' << col << endl;

	int ix = 0, nextrow, nextcol;
	char ch;

	if(tmp.size() > minlenth) goto ret;
	if(row == destrow && col == destcol){
		if(tmp.size() < minlenth){
			minlenth = tmp.size();
			path.assign(tmp.begin(), tmp.end());
		}
		goto ret;
	}

	while(true){
		if(dir == 'N' && ix < maze[row][col].north.size()){
			ch = maze[row][col].north[ix];
			maze[row][col].north[ix] = '-';
		}
		else if(dir == 'S' && ix < maze[row][col].south.size()){
			ch = maze[row][col].south[ix];
			maze[row][col].south[ix] = '-';
		}
		else if(dir == 'W' && ix < maze[row][col].west.size()){
			ch = maze[row][col].west[ix];
			maze[row][col].west[ix] = '-';
		}
		else if(dir == 'E' && ix < maze[row][col].east.size()){
			ch = maze[row][col].east[ix];
			maze[row][col].east[ix] = '-';
		}
		else break;
		if(ch == '-'){++ix; continue;}
		nextrow = row, nextcol = col;
		if(ch == 'N') nextrow--;
		else if(ch == 'S') nextrow++;
		else if(ch == 'E') nextcol++;
		else nextcol--;

        dfs(nextrow, nextcol, ch);

        if(dir == 'N') maze[row][col].north[ix] = ch;
        else if(dir == 'S') maze[row][col].south[ix] = ch;
        else if(dir == 'E') maze[row][col].east[ix] = ch;
        else maze[row][col].west[ix] = ch;
		++ix;
	}
	ret:
	tmp.pop_back();
}

void bfs()

int main(){
    //freopen("1.out", "w", stdout);
	string name, str;
	int currrow, currcol, cnt;
	char dir;
	while(true){
		cin >> name;
		if(name == "END") break;
		//memset(maze, 0, sizeof(maze));
		for(int ix = 1; ix <= 9; ++ix)
            for(int jx = 1; jx <= 9; ++jx){
                maze[ix][jx].north.clear();
                maze[ix][jx].south.clear();
                maze[ix][jx].west.clear();
                maze[ix][jx].east.clear();
        }
		cin >> srcrow >> srccol >> dir >> destrow >> destcol;
		while(true){
			cin >> currrow;
			if(currrow == 0) break;
			cin >> currcol;
			while(true){
				cin >> str;
				if(str[0] == '*') break;
				if(str[0] == 'N')
					maze[currrow][currcol].north = getDir(str);
				else if(str[0] == 'S')
					maze[currrow][currcol].south = getDir(str);
				else if(str[0] == 'E')
					maze[currrow][currcol].east = getDir(str);
				else
					maze[currrow][currcol].west = getDir(str);
                //cout << getDir(str) << endl;
			}
		}
		currrow = srcrow, currcol = srccol;
		if(dir == 'N') currrow--;
		else if(dir == 'S') currrow++;
		else if(dir == 'E') currcol++;
		else currcol--;
		path.clear();
		tmp.clear();
		tmp.emplace_back(srcrow, srccol);
		minlenth = INF;
		dfs(currrow, currcol, dir);
		cout << name << endl;
		if(path.empty()) cout << "  No Solution Possible" << endl;
		else{
			cnt = 0;
			for(point p : path){
				if(cnt) cout << ' ';
				else cout << "  ";
				cout << '(' << p.row << ',' << p.col << ')';
				if(++cnt == 10){
					cout << endl;
					cnt = 0;
				}
			}
			if(cnt) cout << endl;
		}
	}
	return 0;
}
