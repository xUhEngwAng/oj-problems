#include <iostream>
#include <string>
#include <stack>
#include <set>
using namespace std;

void uni(stack<set<string>>& s){
    set<string> one = s.top();
    s.pop();
    set<string> two = s.top();
    s.pop();
    for(string str : one)
        two.insert(str);
    s.push(two);
}

void intersect(stack<set<string>>& s){
    set<string> one = s.top();
    s.pop();
    set<string> two = s.top();
    s.pop();
    set<string> res;
    for(string str : one){
        if(two.find(str) != two.end())
            res.insert(str);
    }
    s.push(res);
}

void add(stack<set<string>>& s){
    set<string> one = s.top();
    s.pop();
    set<string> two = s.top();
    s.pop();
    string res = "{";
    for(string str : one){
        res += str;
        res += ",";
    }
    int len = res.length();
    if(res[len - 1] == ',')
        res[len - 1] = '}';
    else
        res.push_back('}');
    two.insert(res);
    s.push(two);
}

int main(){
	int T, N;
	string cmd;
	stack<set<string>> s;
	cin >> T;
	while(T--){
		cin >> N;
		for(int ix = 0; ix != N; ++ix){
			cin >> cmd;
            if(cmd == "PUSH")
                s.push(set<string>());
            else
            if(cmd == "DUP")
                s.push(s.top());
            else
            if(cmd == "UNION")
                uni(s);
            else
            if(cmd == "INTERSECT")
                intersect(s);
            else
                add(s);
			cout << s.top().size() << endl;
		}
		cout << "***" << endl;
	}
	return 0;
}


