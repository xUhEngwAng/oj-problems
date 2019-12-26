#include <iostream>
#include <stdio.h>

using namespace std;

bool check(int n, int* input, int* output);
bool (*comp)(int one, int two);
bool lt(int one, int two){return one < two;};
bool ge(int one, int two){return one >= two;};

typedef enum {BST, MIRROR, UNDETERMINED} Type;
Type flag = UNDETERMINED;

int main(){
    int N;
    scanf("%d", &N);
    int *input = new int[N], *output = new int[N];
    for(int ix = 0; ix < N; ++ix)
        scanf("%d", &input[ix]);

    if(!check(N, input, output)) printf("NO\n");
    else{
        printf("YES\n");
        printf("%d", output[0]);
        for(int ix = 1; ix != N; ++ix)
            printf(" %d", output[ix]);
    }
    return 0;
}

bool check(int n, int* input, int* output){
    if(n == 0) return true;
    output[n - 1] = input[0];
    if(n == 1) return true;
    //else
    int ix;
    if(flag == UNDETERMINED){
        comp = (input[0] <= input[1]? lt: ge);
        for(ix = 1; !comp(input[ix], input[0]) && ix < n; ++ix);
        if(ix < n){
            for(int jx = ix; jx < n; ++jx)
                if(!comp(input[jx], input[0]))
                    return false;
            flag = (input[0] <= input[1]? MIRROR: BST);
        }
    }
    else{
        comp = (flag == MIRROR? lt: ge);
        for(ix = 1; !comp(input[ix], input[0]) && ix < n; ++ix);
        for(int jx = ix; jx < n; ++jx)
            if(!comp(input[jx], input[0]))
                return false;
    }
    //recursion
    if(!check(ix - 1, input + 1, output)) return false;
    if(!check(n - ix, input + ix, output + ix - 1)) return false;
    return true;
}
