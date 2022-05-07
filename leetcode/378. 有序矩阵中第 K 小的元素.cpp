#include <iostream>
#include <queue>
#include <vector>
using namespace std;

/*
 * 这个题我一开始是用多路归并排序做的，主要熟悉了下
 * priority_queue 的用法，写起来算是比较轻松。然而
 * 这样做的时间复杂度为 O(klogn)，当 k 很大时性能是
 * 比较差的。
 *
 * 看了看答案还有一种二分查找的办法，因为对于任意一
 * 个数字 num，可以在 O(n) 时间内找出矩阵中严格小于
 * 其的数字个数，这样就可以判断后者与 k 的关系，从而
 * 进行二分。这种写法时间复杂度是更优的，但中间要注
 * 意的细节很多，比如如何保证查找的结果一定会出现在
 * 矩阵中，很容易就写错了。
 */

class Node {
public:
    int row;
    int col;
    int val;

    Node() = default;
    Node(int r, int c, int v): row(r), col(c), val(v) {}
};

class Compare {
public:
    bool operator()(const Node& lh, const Node& rh){
        return lh.val > rh.val;
    }
};

class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k){
        int n = matrix.size();
        int begin = matrix[0][0], end = matrix[n-1][n-1]+1, mid, curr;
        while(begin < end - 1){
            mid = (begin + end) >> 1;
            curr = lessThan(matrix, mid);
            if(curr <= k-1) begin = mid;
            else end = mid;
        }

        return begin;
    }

    int lessThan(vector<vector<int>>& matrix, int num){
        int ret = 0, n = matrix.size(), curr = n - 1;

        for(int ix = 0; ix != n; ++ix){
            while(curr >= 0 && num <= matrix[ix][curr]) --curr;
            ret += curr + 1;
        }

        cout << ret << " numbers are less than " << num << endl;

        return ret;
    }

    int kthSmallest_merge_sort(vector<vector<int>>& matrix, int k) { 
        int n = matrix.size(), row, col, val;
        vector<Node> tmp;
        tmp.reserve(n);
        for(int ix = 0; ix != n; ++ix)
            tmp.emplace_back(ix, 0, matrix[ix][0]);
        priority_queue<Node, vector<Node>, Compare> pq(tmp.begin(), tmp.end());

        while(k--){
            Node e = pq.top();
            pq.pop();
            row = e.row, col = e.col, val = e.val;
            if(col < n-1) pq.push(Node(row, col+1, matrix[row][col+1]));
        }

        return val;
    }
};

int main(){
    int n, k;
    cin >> n >> k;
    vector<vector<int>> matrix(n, vector<int>(n));
    for(int ix = 0; ix != n; ++ix)
        for(int jx = 0; jx != n; ++jx)
            cin >> matrix[ix][jx];

    Solution solution;
    int ans = solution.kthSmallest(matrix, k);
    cout << "The answer is " << ans << endl;
    return 0;
}
