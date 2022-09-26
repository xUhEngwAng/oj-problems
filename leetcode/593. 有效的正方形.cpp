/*
 * 这个题确实还挺有趣的，我写了好久，而且还写的特别麻烦。思路上和官方
 * 是类似的，都是三部曲——先判断是平行四边形，然后判断是矩形，最后判断
 * 是正方形。只是我的方法是通过四条边，而官方是通过两条斜边，两条斜边
 * 的中点相同为平行四边形，两条斜边长度相同为矩形，两条斜边垂直为正方
 * 形。这个就是我的知识盲区了...毕竟数学不太好。
 *
 * 另外关于如何找到斜边，我是用了一个叉积来判断，官方是遍历所有的情况，
 * 只能说差不多吧。
 */

class Vec2 {
public:
    int x, y;
    Vec2() = default;
    Vec2(int _x, int _y): x(_x), y(_y) {}
    Vec2(vector<int>& p): x(p[0]), y(p[1]) {}

    Vec2 operator+(const Vec2& rhv){
        return Vec2(x+rhv.x, y+rhv.y);
    }

    bool operator==(const Vec2& rhv){
        return x == rhv.x && y == rhv.y;
    }

    bool operator!=(const Vec2& rhv){
        return x != rhv.x || y != rhv.y;
    }

    int dot(const Vec2& rhv){
        return x * rhv.x + y * rhv.y;
    }

    int cross(const Vec2& rhv){
        int res = x * rhv.y - y * rhv.x;
        if(res > 0) return 1;
        else if(res < 0) return -1;
        return 0;
    }
};

class Solution {
public:
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        vector<vector<int>> points = {p1, p2, p3, p4};
        Vec2 e1(p2[0]-p1[0], p2[1]-p1[1]);
        Vec2 e2(p3[0]-p1[0], p3[1]-p1[1]);
        Vec2 e3(p4[0]-p1[0], p4[1]-p1[1]);
        if(e1.cross(e2) * e1.cross(e3) < 0) {
            points[1] = p3;
            points[2] = p2;
        }
        else if(e3.cross(e1) * e3.cross(e2) < 0) {
            points[2] = p4;
            points[3] = p3;
        }
        return isSquare(points);
    }

    bool isSquare(const vector<vector<int>>& points){
        Vec2 e1(points[1][0]-points[0][0], points[1][1]-points[0][1]);
        Vec2 e2(points[2][0]-points[1][0], points[2][1]-points[1][1]);
        Vec2 e3(points[3][0]-points[2][0], points[3][1]-points[2][1]);
        Vec2 e4(points[0][0]-points[3][0], points[0][1]-points[3][1]);
        if(e1 + e3 != Vec2() || e2 + e4 != Vec2()) return false;
        if(e1.dot(e2)) return false;
        if(!(abs(e1.x) + abs(e2.x)) || abs(e1.x) != abs(e2.y) || abs(e1.y) != abs(e2.x)) return false;
        return true;
    }
};
