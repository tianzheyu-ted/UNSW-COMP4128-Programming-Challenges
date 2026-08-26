
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


struct Point {
    long long x, y;
};

struct Star {
    long long x, y;
    int id;
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

    vector<Star> stars(n);
    for (int i = 0; i < n; i++) {
        cin >> stars[i].x;
        cin >> stars[i].y;
        stars[i].id = i + 1;
    }

    sort(stars.begin(), stars.end(), [] (auto& a, auto& b) {
        if (a.x == b.x) {
            return a.y < b.y;
        }
        return a.x < b.x;
    });

    auto a = stars[0];
    auto b = stars[1];

    for (int i = 2; i < n; i++) {
        auto c = stars[i];
        if (ccw({a.x, a.y}, {b.x, b.y}, {c.x, c.y}) != 0) {
            cout << a.id << ' ' << b.id << ' ' << c.id << '\n';
            return 0;
        }
    }
}