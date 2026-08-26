
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
    vector<Point> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i].x >> A[i].y;
    }

    int m;
    cin >> m;
    vector<Point> B(m);
    for (int i = 0; i < m; i++) {
        cin >> B[i].x >> B[i].y;
    }

    /**
     * return value > 0: OV is in the counter-clockwise direction of OU.
     * return value < 0: OV is in the clockwise direction of OU.
     */
    auto cross_product = [] (Point O, Point U, Point V) -> long long {
        return (U.x - O.x) * (V.y - O.y) - (U.y - O.y) * (V.x - O.x);
    };

    bool ok = true;
    for (auto& point : B) {
        if (
            cross_product(A[0], A[1], point) >= 0
            || cross_product(A[0], A[n - 1], point) <= 0
        ) {
            ok = false;
            break;
        }

        int lo = 1;
        int hi = n - 1;
        while (hi - lo > 1) {
            int mid = lo + (hi - lo) / 2;
            if (cross_product(A[0], A[mid], point) < 0) {
                lo = mid;
            } else {
                hi = mid;
            }
        }

        if (cross_product(A[lo], A[hi], point) >= 0) {
            ok = false;
            break;
        }
    }

    if (ok) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}