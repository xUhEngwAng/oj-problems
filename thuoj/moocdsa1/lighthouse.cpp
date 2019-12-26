#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

class quatTreeNode{
public:
	int x;
	int y;
	int count;											//count the number of nodes in the tree
	quatTreeNode *first, *second, *third, *fourth;
	//constructor
	quatTreeNode(int x, int y):x(x), y(y), count(1){
		first = second = third = fourth = nullptr;
	}
};

class quatTree{
public:
	quatTreeNode* root = nullptr;

	void insert(int xpos, int ypos) {
		quatTreeNode* newNode = new quatTreeNode(xpos, ypos);
		if (!root) root = newNode;
		else{
			quatTreeNode* curr = root;
			curr->count++;
			while(true){
				if(xpos > curr->x && ypos > curr->y){//fisrt section
					if (!curr->first) {
						curr->first = newNode;
						break;
					}
					curr = curr->first;
				}
				else if (xpos < curr->x && ypos > curr->y) {//second section
					if (!curr->second) {
						curr->second = newNode;
						break;
					}
					curr = curr->second;
				}
				else if (xpos < curr->x && ypos < curr->y) {//third section
					if (!curr->third) {
						curr->third = newNode;
						break;
					}
					curr = curr->third;
				}
				else{//fourth section
					if (!curr->fourth) {
						curr->fourth = newNode;
						break;
					}
					curr = curr->fourth;
				}
				curr->count++;
			}
		}
	}
};

int dfs_count(quatTreeNode* node){
	int sum = 0;
	if (node->first)  sum += dfs_count(node->first) + node->first->count;
	if (node->second) sum += dfs_count(node->second);
	if (node->third)  sum += dfs_count(node->third) + node->third->count;
	if (node->fourth) sum += dfs_count(node->fourth);
	return sum;
}

int main_(){
	int n;
	scanf("%d", &n);
	quatTree tree;
	int xpos, ypos;
	for (int ix = 0; ix != n; ++ix) {
		scanf("%d %d", &xpos, &ypos);
		tree.insert(xpos, ypos);
	}
	printf("%d", dfs_count(tree.root));
	//while (getchar() != ' ');
	return 0;
}
