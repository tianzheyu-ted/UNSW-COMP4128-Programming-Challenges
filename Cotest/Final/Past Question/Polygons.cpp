
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


struct Point {
    long long x, y;
    bool operator<(const Point& o) const {
        if (x != o.x) return x < o.x;
        return y < o.y;
    }
};

auto sortByCCW_Integer = [](vector<Point>& points) {
    Point center = {0, 0};
    for (const auto& p : points) {
        center.x += p.x;
        center.y += p.y;
    }
    center.x /= (long long)points.size();
    center.y /= (long long)points.size();

    auto half_plane = [](Point p) -> int {
        return (p.y > 0 || (p.y == 0 && p.x >= 0)) ? 1 : 0;
    };
    sort(points.begin(), points.end(), [&](const Point& a, const Point& b) {
        Point va = {a.x - center.x, a.y - center.y};
        Point vb = {b.x - center.x, b.y - center.y};
        int h1 = half_plane(va);
        int h2 = half_plane(vb);
        if (h1 != h2) return h1 > h2;
        long long cross = va.x * vb.y - va.y * vb.x;
        if (cross != 0) return cross > 0;
        long long dist_a = va.x * va.x + va.y * va.y;
        long long dist_b = vb.x * vb.x + vb.y * vb.y;
        return dist_a < dist_b;
    });
};

auto ccw = [](Point a, Point b, Point c) -> int {
    long long cross = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (cross > 0) return 1;
    if (cross < 0) return -1;
    return 0;
};

auto get_convex_hull = [](vector<Point> pts) -> vector<Point> {
    int n = pts.size(), k = 0;
    if (n <= 2) return pts;
    vector<Point> hull(2 * n);
    sort(pts.begin(), pts.end());
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && ccw(hull[k - 2], hull[k - 1], pts[i]) <= 0) k--;
        hull[k++] = pts[i];
    }
    for (int i = n - 2, t = k + 1; i >= 0; i--) {
        while (k >= t && ccw(hull[k - 2], hull[k - 1], pts[i]) <= 0) k--;
        hull[k++] = pts[i];
    }
    hull.resize(k - 1);
    return hull;
};

int main() {
    int n;
    std::cin >> n;
    
    set<Point> A;
    vector<Point> points(n, {-1, -1});
    for (int i = 0; i < n; i++) {
        std::cin >> points[i].x >> points[i].y;
        A.insert({points[i].x, points[i].y});
    }

    int m;
    std::cin >> m;
    points.reserve(m);

    vector<Point> B(m, {-1, -1});
    for (int i = 0; i < m; i++) {
        std::cin >> B[i].x >> B[i].y;
        points.push_back({B[i].x, B[i].y});
    }

    sortByCCW_Integer(points);

    auto convex_hull = get_convex_hull(points);

    for (auto point : convex_hull) {
        if (!A.count(point)) {
            cout << "NO\n";
            return 0;
        }
    }

    cout << "YES\n";
}