
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// 强烈建议定义一个简单的 Point 结构体，比 pair 更好读
struct Point {
    long long x, y;
    bool operator<(const Point& o) const {
        if (x != o.x) return x < o.x;
        return y < o.y;
    }
};

// CCW 测试 Lambda
// 返回值: 1 (左转/逆时针), -1 (右转/顺时针), 0 (三点共线)
auto ccw = [](Point a, Point b, Point c) -> int {
    // 向量 AB = (b.x - a.x, b.y - a.y)
    // 向量 AC = (c.x - a.x, c.y - a.y)
    // 叉积 AB x AC = (AB.x * AC.y) - (AB.y * AC.x)
    long long cross = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (cross > 0) return 1;  // 叉积大于 0 代表向左转 (逆时针)
    if (cross < 0) return -1; // 叉积小于 0 代表向右转 (顺时针)
    return 0;                 // 叉积等于 0 意味着三点共线
};

auto check_intersect = [&](Point a, Point b, Point c, Point d) -> bool {
    // 辅助函数：判断点 p 是否在线段 ab 的矩形包围盒内（用于处理三点共线）
    auto on_segment = [](Point p, Point a, Point b) {
        return p.x >= min(a.x, b.x) && p.x <= max(a.x, b.x) &&
               p.y >= min(a.y, b.y) && p.y <= max(a.y, b.y);
    };
    int cp1 = ccw(a, b, c);
    int cp2 = ccw(a, b, d);
    int cp3 = ccw(c, d, a);
    int cp4 = ccw(c, d, b);
    // 1. 规范相交：相互跨立，叉积符号必定相反
    if (cp1 * cp2 < 0 && cp3 * cp4 < 0) return true;
    // 2. 非规范相交：端点相连或三点共线，且必须落在对方的包围盒内
    if (cp1 == 0 && on_segment(c, a, b)) return true;
    if (cp2 == 0 && on_segment(d, a, b)) return true;
    if (cp3 == 0 && on_segment(a, c, d)) return true;
    if (cp4 == 0 && on_segment(b, c, d)) return true;
    return false;
};

// 示例：示范如何使用 Lambda 对点集按逆时针顺序排序

// ==========================================
// 方法一：纯整数叉积极角排序 Lambda（推荐！零精度误差）
// ==========================================
auto sortByCCW_Integer = [](vector<Point>& points) {
    Point center = {0, 0};
    for (const auto& p : points) {
        center.x += p.x;
        center.y += p.y;
    }
    center.x /= (long long)points.size();
    center.y /= (long long)points.size();

    // 判断点位于中心点的上半平面还是下半平面
    auto half_plane = [](Point p) -> int {
        return (p.y > 0 || (p.y == 0 && p.x >= 0)) ? 1 : 0;
    };

    sort(points.begin(), points.end(), [&](const Point& a, const Point& b) {
        // 计算相对中心的向量
        Point va = {a.x - center.x, a.y - center.y};
        Point vb = {b.x - center.x, b.y - center.y};

        int h1 = half_plane(va);
        int h2 = half_plane(vb);

        // 不在同一半平面，上半平面的点排在前面
        if (h1 != h2) return h1 > h2;

        // 在同一半平面内，利用二维叉积判断左右走向
        // 叉积 > 0 说明 va 在 vb 的逆时针方向（右侧向量转到左侧向量）
        long long cross = va.x * vb.y - va.y * vb.x;
        if (cross != 0) return cross > 0;

        // 共线/极角相同时，按距离中心的平方升序排列
        long long dist_a = va.x * va.x + va.y * va.y;
        long long dist_b = vb.x * vb.x + vb.y * vb.y;
        return dist_a < dist_b;
    });
};


// ==========================================
// 方法二：atan2 角度排序 Lambda（极其好记，但有浮点精度风险）
// ==========================================
auto sortByCCW_Atan2 = [](vector<Point>& points) {
    Point center = {0, 0};
    for (const auto& p : points) {
        center.x += p.x;
        center.y += p.y;
    }
    center.x /= (long long)points.size();
    center.y /= (long long)points.size();

    sort(points.begin(), points.end(), [&](const Point& a, const Point& b) {
        double angle_a = atan2(a.y - center.y, a.x - center.x);
        double angle_b = atan2(b.y - center.y, b.x - center.x);
        
        // 角度不相等时按角度升序（逆时针）
        if (std::abs(angle_a - angle_b) > 1e-9) {
            return angle_a < angle_b;
        }
        
        // 角度相同时按距离远近排序
        long long dist_a = (a.x - center.x) * (a.x - center.x) + (a.y - center.y) * (a.y - center.y);
        long long dist_b = (b.x - center.x) * (b.x - center.x) + (b.y - center.y) * (b.y - center.y);
        return dist_a < dist_b;
    });
};

// 传入的 pts 必须是按顺序（顺时针或逆时针均可）给出的多边形顶点
auto polygon_area = [](const vector<Point>& pts) -> double {
    long long area = 0;
    int n = pts.size();
    
    for (int i = 0; i < n; i++) {
        Point p1 = pts[i];
        Point p2 = pts[(i + 1) % n]; // 最后一个点与第一个点闭合
        // 原点 (0,0) 到 p1, p2 的三角形叉积
        area += (p1.x * p2.y - p2.x * p1.y); 
    }
    
    // 取绝对值并除以 2
    return abs(area) / 2.0; 
};


// 传入点集，返回构成凸包的顶点（逆时针顺序）
auto get_convex_hull = [&](vector<Point> pts) -> vector<Point> {
    int n = pts.size(), k = 0;
    if (n <= 2) return pts;
    
    vector<Point> hull(2 * n);
    // 1. 必须先排序（先按 X 排，再按 Y 排）
    sort(pts.begin(), pts.end());

    // 2. 构造下半凸壳
    for (int i = 0; i < n; ++i) {
        // 如果新加入的点导致了左转或直行（ccw <= 0 剔除共线点），则弹出栈顶
        while (k >= 2 && ccw(hull[k - 2], hull[k - 1], pts[i]) <= 0) k--;
        hull[k++] = pts[i];
    }
    
    // 3. 构造上半凸壳
    for (int i = n - 2, t = k + 1; i >= 0; i--) {
        while (k >= t && ccw(hull[k - 2], hull[k - 1], pts[i]) <= 0) k--;
        hull[k++] = pts[i];
    }
    
    // 最后一个点和第一个点重复了，删去
    hull.resize(k - 1);
    return hull;
};


double distanceBetweenPoints(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// 求点 p0 到经过点 p1 和 p2 的直线的距离
double pointToLineDistance(Point p0, Point p1, Point p2) {
    // 处理 p1 和 p2 重合的异常情况（此时无法确定一条直线）
    if (p1.x == p2.x && p1.y == p2.y) {
        return distanceBetweenPoints(p0, p1);
    }

    // 分子：向量叉积的绝对值 (面积)
    double area = abs((p2.x - p1.x) * (p0.y - p1.y) - (p2.y - p1.y) * (p0.x - p1.x));
    
    // 分母：直线段 p1p2 的长度 (底边长)
    double base = distanceBetweenPoints(p1, p2);
    
    // 距离 = 面积 / 底边长
    return area / base;
}