#include <vector>
#include <cstdio>
#define SIZE 9

using std::vector;
using std::pair;

/*
 * 尽管这个题有一些巧妙的思路，比如先把可以唯一确定的位置
 * 给确定了云云，但我最终还是使用了DFS来爆搜，yet 一开始的
 * 性能特别慢。后来发现是因为我的最内层循环，即判断填某个
 * 数字是否在行、列、九宫格内重复太慢了，因为对于填的每个
 * 数字我都要遍历一遍对应的行/列/九宫格。
 *
 * 后来的优化方案是，使用了一个矩阵来保存，某一行是否出现
 * 某个数字，对于列和九宫格也是同理。这样处理了以后速度快
 * 了 40 倍不止。理论上时间复杂度都是 O(1)，但优化内层循环
 * 作用还是很明显的。
 */

class Solution {
public:
    vector<vector<bool>> row_exist, col_exist, sqr_exist;

    void solveSudoku(vector<vector<char>>& board) {
        int curr, row, col, sqr_row, sqr_col;
        pair<int, int> next_pair;
        row_exist.resize(SIZE, vector<bool>(SIZE, false));
        col_exist.resize(SIZE, vector<bool>(SIZE, false));
        sqr_exist.resize(SIZE, vector<bool>(SIZE, false));

        for(int ix = 0; ix != SIZE; ++ix){
            for(int jx = 0; jx != SIZE; ++jx){
                if(board[ix][jx] != '.'){
                    curr = board[ix][jx] - '1';
                    sqr_row = ix / 3;
                    sqr_col = jx / 3;
                    row_exist[ix][curr] = true;
                    col_exist[jx][curr] = true;
                    sqr_exist[sqr_row * 3 + sqr_col][curr] = true;
                }
            }
        }
 
        next_pair = next(board, -1, SIZE-1);
        row = next_pair.first;
        col = next_pair.second;

        dfs(board, row, col);
    }

    bool dfs(vector<vector<char>>& board, int row, int col){
        if(row == -1 && col == -1) return true;

        pair<int, int> next_pair = next(board, row, col);
        int sqr_idx = (row / 3) * 3 + col / 3;

        for(int val = 0; val != 9; ++val){
            if(row_exist[row][val] || col_exist[col][val] || sqr_exist[sqr_idx][val])
                continue;

            board[row][col] = val + '1';
            row_exist[row][val] = true;
            col_exist[col][val] = true;
            sqr_exist[sqr_idx][val] = true;
            
            if(dfs(board, next_pair.first, next_pair.second))
                return true;
            
            row_exist[row][val] = false;
            col_exist[col][val] = false;
            sqr_exist[sqr_idx][val] = false;
        }

        board[row][col] = '.';
        return false;
    }

    pair<int, int> next(vector<vector<char>>& board, int row, int col){
        int next_row = row, next_col = col;

        while(true){
            next_col += 1;
            if(next_col == SIZE){
                next_col  = 0;
                next_row += 1;
                if(next_row == SIZE)
                    return pair<int, int>(-1, -1);
            }
            if(board[next_row][next_col] == '.')
                break;
        }

        return pair<int, int>(next_row, next_col);
    }
};

int main(){
    vector<vector<char>> board(SIZE, vector<char>(SIZE, '.'));
    for(int ix = 0; ix != SIZE; ++ix)
        for(int jx = 0; jx != SIZE; ++jx)
            scanf("%c ", &board[ix][jx]);

    for(int ix = 0; ix != SIZE; ++ix){
        for(int jx = 0; jx != SIZE; ++jx){
            printf("%c ", board[ix][jx]);   
        }
        printf("\n");
    }

    Solution solution;
    solution.solveSudoku(board);
    for(int ix = 0; ix != SIZE; ++ix){
        for(int jx = 0; jx != SIZE; ++jx){
            printf("%c ", board[ix][jx]);   
        }
        printf("\n");
    }

   return 0;
}
