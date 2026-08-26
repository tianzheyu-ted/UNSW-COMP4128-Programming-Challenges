
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Point {
    long long x;
    long long y;
};

int main() {
    int n;
    cin >> n;

    vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
    }

    auto check_collinearity = [] (Point a, Point b, Point c) -> bool {
        return (((a.y - b.y) * (b.x - c.x)) == ((b.y - c.y) * (a.x - b.x)));
    };

    auto A = points[0];
    auto B = points[1];
    auto C = points[2];

    auto helper = [&] (Point X, Point Y) {
        vector<Point> remianing; remianing.reserve(n);
        for (auto& point : points) {
            if (!check_collinearity(X, Y, point)) {
                remianing.push_back(point);
            }
        }
        if (remianing.size() < 3) {
            return true;
        } else {
            auto C = remianing[0];
            auto D = remianing[1];
            for (auto point : remianing) {
                if (!check_collinearity(C, D, point)) {
                    return false;
                }
            }
            return true;
        }
    };
    
    bool result = helper(A, B) | helper(B, C) | helper(A, C);

    if (result) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}