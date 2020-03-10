#include <iostream>
#include <string>
#include <queue>
#include <vector>
using namespace std;

/* 
 * 在建树过程中判断是否给同一个节点指派了多个值；在 bfs
 * 中判断是否存在没有指派值的节点即可。
 */

struct node{
	int value = -1;
	node *left = nullptr;
	node *right = nullptr;
};

node *root, *curr;

bool insert(int value, string path){
	curr = root;
	for(int ix = 0; ix != path.size(); ++ix){
		if(path[ix] == 'L'){
			if(curr->left == nullptr)
				curr->left = new node;
			curr = curr->left;
		}
		else{
			if(curr->right == nullptr)
				curr->right = new node;
			curr = curr->right;
		}
	}
	if(curr->value != -1) return true;
	curr->value = value;
	return false;
}

int main(){
	int value, pos;
	string path, str;
	bool flag;
	queue<node*> q;
	vector<int> res;
	while(cin >> str){
	    pos = str.find(',');
        value = stoi(str.substr(1, pos - 1));
        path = str.substr(pos + 1);
        path.pop_back();
		root = new node;
		flag = false;
		insert(value, path);
		while(true){
            cin >> str;
            if(str == "()") break;
			if(flag) continue;
            pos = str.find(',');
            value = stoi(str.substr(1, pos - 1));
            path = str.substr(pos + 1);
            path.pop_back();
			flag = insert(value, path);
		}
		if(flag) goto ret;
		res.clear();
        while(!q.empty()) q.pop();
		q.push(root);
		while(!q.empty()){
			curr = q.front();
			q.pop();
			if(curr->value == -1) {flag = true; goto ret;}
			res.push_back(curr->value);
			if(curr->left)  q.push(curr->left);
			if(curr->right) q.push(curr->right);
		}
		ret:
		if(flag) printf("not complete\n");
		else{
			printf("%d", res[0]);
			for(int ix = 1; ix != res.size(); ++ix)
				printf(" %d", res[ix]);
			printf("\n");
		}
	}
	return 0;
}
