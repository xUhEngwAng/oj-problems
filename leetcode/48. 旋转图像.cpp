#include <vector>
using std::vector;

/*
 * 对于某个坐标 (x, y)，假设图像的大小为 n，旋转 90 度
 * 以后的坐标为 (y, n - 1 - x)，利用图形学里的 transformation
 * 很容易证明这个结论。
 */

class Solution{
public:
    void rotate(vector<vector<int>>& matrix){
        int curr, prev;
        int x, y, next_x, next_y, n = matrix.size();
        
        for(x = 0; x <= n >> 1; ++x){
            for(y = x; y < n-x-1; ++y){
                prev = matrix[x][y];

                for(int ix = 0; ix != 4; ++ix){
                    next_x = y, next_y = n - 1 - x;
                    curr = matrix[next_x][next_y];
                    matrix[next_x][next_y] = prev;

                    x = next_x, y = next_y;
                    prev = curr;
                }
            }
        }
    }
};
