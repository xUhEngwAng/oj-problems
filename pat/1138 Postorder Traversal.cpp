#include <cstdio>

int main(){
	int N; 
	scanf("%d", &N);
	int *preorder = new int[N];
	int *inorder  = new int[N];
	for(int ix = 0; ix != N; ++ix)
		scanf("%d", preorder + ix);
	for(int ix = 0; ix != N; ++ix)
		scanf("%d", inorder + ix);
	int pos;
	while(true){
		if(N == 1) break;
		pos = 0;
		while(inorder[pos] != preorder[0]) ++pos;
		if(pos == 0){
			inorder = inorder + 1;
			preorder = preorder + 1;
			N--;
		}
		else{
			preorder = preorder + 1;
			N = pos;
		}
	}
	printf("%d\n", inorder[0]);
	return 0;
}
