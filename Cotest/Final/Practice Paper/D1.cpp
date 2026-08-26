
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

struct Point {
    long long x, y;
};

double distanceBetweenPoints(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

double pointToLineDistance(Point p0, Point p1, Point p2) {
    if (p1.x == p2.x && p1.y == p2.y) {
        return distanceBetweenPoints(p0, p1);
    }
    double area = abs((p2.x - p1.x) * (p0.y - p1.y) - (p2.y - p1.y) * (p0.x - p1.x));
    double base = distanceBetweenPoints(p1, p2);
    return area / base;
}

int main() {
    int n;
    long long A;
    cin >> n >> A;

    vector<Point> points(n, {-1, -1});
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
    }

    Point p1 = points[0];
    Point p2;
    for (int i = 1; i < n; i++) {
        p2 = points[i];
        double max_dist = 0;
        for (Point p : points) {
            max_dist = max(max_dist, pointToLineDistance(p, p1, p2));
        }
        cout << max_dist << '\n';
        p1 = p2;
    }

    p2 = points[0];
    double max_dist = 0;
    for (Point p : points) {
        max_dist = max(max_dist, pointToLineDistance(p, p1, p2));
    }
    cout << max_dist << '\n';
}