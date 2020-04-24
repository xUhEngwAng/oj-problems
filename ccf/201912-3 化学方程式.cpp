#include <map>
#include <string>
#include <iostream>
using namespace std;

map<string, int> leftmap;
map<string, int> rightmap;
map<string, int>::iterator it1, it2;

map<string, int> parse(const string &term){
	map<string, int> res, tmp;
	int pos = 0, cnt = 0, endpos, suffix, ix;
	string curr;
	while(pos < term.size()){
		if(term[pos] == '('){
			cnt = 1;
			for(endpos = pos + 1; cnt != 0; ++endpos){
				if(term[endpos] == '(') ++cnt;
				if(term[endpos] == ')') --cnt;
			}
			for(ix = endpos; ix < term.size() && isdigit(term[ix]); ++ix);
			if(ix == endpos) suffix = 1;
			else suffix = stoi(term.substr(endpos, ix - endpos));
			//cout << term.substr(pos, endpos - pos);
			//cout << suffix << endl;
			//system("pause");
			tmp = parse(term.substr(pos + 1, endpos - pos - 2));
			for(auto it = tmp.begin(); it != tmp.end(); ++it)
				res[it->first] += it->second * suffix;
		}
		else{
			for(endpos = pos + 1; islower(term[endpos]); ++endpos);
			curr = term.substr(pos, endpos - pos);
			for(ix = endpos; ix < term.size() && isdigit(term[ix]); ++ix);
			if(ix == endpos) suffix = 1;
			else suffix = stoi(term.substr(endpos, ix - endpos));
			res[curr] += suffix;
		}
		pos = ix;
	}
	return res;
}

void parseExpr(const string &expr, bool isleft){
	int beg = 0, pos = 0, coef, ix;
	map<string, int> tmp;
	while(true){
		ix = beg;
		for(; isdigit(expr[beg]); ++beg);
		if(beg == ix) coef = 1;
		else          coef = stoi(expr.substr(ix, beg - ix));
		//cout << coef << endl;

		pos = expr.find('+', beg);
		if(pos == -1)
			tmp = parse(expr.substr(beg));
		else{
			tmp = parse(expr.substr(beg, pos - beg));
			beg = pos + 1;
		}
		for(auto it = tmp.begin(); it != tmp.end(); ++it)
			if(isleft) leftmap[it->first] += it->second * coef;
			else rightmap[it->first] += it->second * coef;
		if(pos == -1) break;
	}
}

int main(){
    //freopen("201912-3.in", "r", stdin);
	int n, pos;
	cin >> n;
	string equation, left, right;
	while(n--){
		cin >> equation;
		leftmap.clear();
		rightmap.clear();
		pos = equation.find('=');
		left = equation.substr(0, pos);
		right = equation.substr(pos + 1);
		parseExpr(left, 1);
		/*for(it1 = leftmap.begin(); it1 != leftmap.end(); ++it1)
            cout << it1->first << ": " << it1->second << endl;*/
		parseExpr(right, 0);
		if(leftmap.size() != rightmap.size()){
			printf("N\n");
			continue;
		}
        /*for(it2 = rightmap.begin(); it2 != rightmap.end(); ++it2)
            cout << it2->first << ": " << it2->second << endl;*/
		for(it1 = leftmap.begin(), it2 = rightmap.begin();
		    it1 != leftmap.end(); ++it1, ++it2){
			if(it1->first != it2->first || it1->second != it2->second){
				printf("N\n");
				break;
			}
		}
		if(it1 == leftmap.end()) printf("Y\n");
	}
	return 0;
}
