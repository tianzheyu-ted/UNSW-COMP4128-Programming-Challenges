
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


struct Point {
    int id;
    long long x, y;
    bool operator<(const Point& o) const {
        if (x != o.x) return x < o.x;
        return y < o.y;
    }
};

auto ccw = [](Point a, Point b, Point c) -> int {
    long long cross = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (cross > 0) return 1;
    if (cross < 0) return -1;
    return 0;
};

int main() {
    int n;
    cin >> n;

    vector<Point> ordered_points(n, {-1, -1, -1});
    vector<Point> points(n, {-1, -1, -1});
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
        points[i].id = i;
        ordered_points[i] = {points[i].id, points[i].x, points[i].y};
    }

    if (n <= 3) {
        cout << "YES\n";
        return 0;
    }

    Point A = points[0];
    Point B = points[1];
    Point C = points[2];

    auto check = [&] (Point p1, Point p2) -> bool {
        set<int> s;
        for (auto& p : points) {
            if (ccw(p1, p2, p) != 0) {
                s.insert(p.id);
            }
        }

        if (s.size() <= 2) {
            return true;
        }

        Point D = points[*s.begin()];
        Point E = points[*next(s.begin())];

        for (auto& id : s) {
            if (ccw(D, E, points[id]) != 0) {
                return false;
            }
        }

        return true;
    };

    if (check(A, B) || check(B, C) || check(A, C)) {
        cout << "YES\n";
        return 0;
    }
    
    cout << "NO\n";
}