#include <iostream>
#include <vector>
using std::vector;

class Matrix2 {
public:
    vector<vector<int>> mat;

    Matrix2() { mat.resize(2, vector<int>(2)); };
    Matrix2(int a, int b, int c, int d){
        mat.resize(2, vector<int>(2));
        mat[0][0] = a;
        mat[0][1] = b;
        mat[1][0] = c;
        mat[1][1] = d;
    }

    vector<int> operator[](int ix) const {
        return mat[ix];
    }

    Matrix2 multiply(const Matrix2& rhm){
        int a = mat[0][0] * rhm[0][0] + mat[0][1] * rhm[1][0];
        int b = mat[0][0] * rhm[0][1] + mat[0][1] * rhm[1][1];
        int c = mat[1][0] * rhm[0][0] + mat[1][1] * rhm[1][0];
        int d = mat[1][0] * rhm[0][1] + mat[1][1] * rhm[1][1];
        return Matrix2(a, b, c, d);
    }

    Matrix2 power(int n){
        Matrix2 ret = Matrix2(1, 0, 0, 1), curr = *this;

        while(n){
            if(n & 1) ret = ret.multiply(curr);
            curr = curr.multiply(curr);
            n = n >> 1;
        }

        return ret;
    }
};

class Solution {
public:
    int fib(int n) {
        Matrix2 m(1, 1, 1, 2);
        m = m.power(n >> 1);
        
        if(n & 1) return m[1][1];
        else return m[0][1];
    }
};

int main(){
    int n;
    std::cin >> n;
    Solution solution;

    for(int ix = 0; ix <= n; ++ix){
        std::cout << "fib(" << ix << ") = " << solution.fib(ix) << std::endl;
    }

    return 0;
}
