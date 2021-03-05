class Solution {
public:
    void merge(int A[], int m, int B[], int n) {
        int *tmp = new int[m];
        
        for(int ix = 0; ix != m; ++ix){
            tmp[ix] = A[ix];
        }
        
        for(int ix = 0, jx = 0; ix != m || jx != n;){
            if(ix == m){
                A[ix+jx] = B[jx];
                ++jx;
                continue;
            }
            if(jx == n){
                A[ix+jx] = tmp[ix];
                ++ix;
                continue;
            }
            if(tmp[ix] < B[jx]){
                A[ix+jx] = tmp[ix];
                ++ix;
            }
            else{
                A[ix+jx] = B[jx];
                ++jx;
            }
        }
    }
};