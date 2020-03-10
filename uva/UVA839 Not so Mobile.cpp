#include <cstdio>
#include <stack>
#include <vector>
using namespace std;

/*
 * 这个题也不过如此啊，我还以为会很难呢。具体的思路如下：
 *
 * 采用一个满二叉树来表示这样一个嵌套的天平。对任意一个节点，
 * 其左子树为左边的天平，左子边是该天平距离支点的距离，右边
 * 同理。
 * 
 * 首先是输入，题目中显然是一种递归地输入形式，因此引入一个栈
 * 来保存所有重量为零的节点，如果左右的重量都为零，则右边首先
 * 入栈，然后左边入栈。
 *
 * 对平衡性地判断也是递归地进行，为了判断当前天平（节点）是否
 * 平衡，首先需要计算其左子树的重量，以及右子树的重量，再判断
 * 两者是否满足平衡的充要条件，该过程递归地进行。如果某个子天平
 * 不平衡，则返回权重为 -1，表示这一情况。
 *
 * 我的思路和紫书上面是完全一样的，只不过紫书的参考答案把读入
 * 和平衡判断放到了一起，因为两者本质上都是先序遍历，这样确实
 * 非常巧妙，还不用额外的空间来存储数据。我还犯了一个愚蠢的错误，
 * 即每个 test case 后没有把上一轮的树清空，导致我 debug 半天。
 */

struct node{
	int weight;
	int leftdist;
	int rightdist;
	int left = -1, right = -1;
};

vector<node> tree;

int computeWeight(int root){
	if(tree[root].left == -1 && tree[root].right == -1)
		return tree[root].weight;
	int leftweight = computeWeight(tree[root].left);
	if(leftweight == -1) return -1;
	int rightweight = computeWeight(tree[root].right);
	if(rightweight == -1) return -1;
	if(leftweight * tree[root].leftdist !=
	   rightweight * tree[root].rightdist)
		return -1;
    //printf("%d\n", leftweight + rightweight);
	return leftweight + rightweight;
}

int main(){
    //freopen("1.out", "w", stdout);
	int n, curr, wl, wr, dl, dr, cnt;
	scanf("%d", &n);
	stack<int> s;
	node tmp;
	int res;
	while(n--){
		cnt = 1;
		tmp.weight = 0;
		tree.clear();
		tree.push_back(tmp);
		s.push(0);
		while(!s.empty()){
			curr = s.top();
			s.pop();
			scanf("%d %d %d %d", &wl, &dl, &wr, &dr);
			tree[curr].leftdist = dl;
			tree[curr].rightdist = dr;
			tmp.weight = wl;
			tree.push_back(tmp);
			tree[curr].left = cnt++;
			tmp.weight = wr;
			tree.push_back(tmp);
			tree[curr].right = cnt++;
			if(wr == 0) s.push(tree[curr].right);
			if(wl == 0) s.push(tree[curr].left);
		}
		res = computeWeight(0);
		if(res != -1) printf("YES\n");
		else printf("NO\n");
		if(n) printf("\n");
	}
	return 0;
}
