#include <cstdio>
#define LEFTCHILD(X)  (X << 1)
#define RIGHTCHILD(X) ((X << 1) + 1)

/*
 * 此题颇有意思啊，一开始我是暴力模拟，设满二叉树的深度为 d，
 * 时间复杂度为 O(d x 2^d)，最多据说有 1000 个测试点，所以
 * 超时了。
 *
 * 经过一番思考后想出了高效算法，对于每个测试点时间复杂度仅为
 * O(d)，描述如下
 *
 * 1. 设 I = iter，则是第 iter 次访问根节点。如果 iter 是
 *    偶数，小球应该沿右侧路径滚下，否则沿着左侧路径滚下。
 * 2. 如果沿着右侧路径，则这是右子树的根节点的第 iter / 2
 *    次访问；如果沿左侧路径，则这是左子树的根节点的第
 *    iter / 2 + 1 次访问。
 * 3. 递归地沿着左右子树不断滚下，直到叶节点。
 */

int main(){
	int n, depth, iter, curr;
	scanf("%d", &n);
	while(n--){
		scanf("%d %d", &depth,  &iter);
		curr = 1;
		for(int ix = 1; ix < depth; ++ix){
			if(iter & 1){
				curr = LEFTCHILD(curr);
				iter = (iter >> 1) + 1;
			}else{
				curr = RIGHTCHILD(curr);
				iter = iter >> 1;
			}
		}
		printf("%d\n", curr);
	}
	scanf("%d", &curr);
	return 0;
}
