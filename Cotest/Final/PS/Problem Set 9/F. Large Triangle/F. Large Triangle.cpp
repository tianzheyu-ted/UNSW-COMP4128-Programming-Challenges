
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Point {
    long long x, y;
};

struct Edge {
    int u, v;
};

int main() {
    int n;
    long long S;
    cin >> n >> S;

    vector<Point> points(n, {0, 0});
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
    }

    sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });

    vector<Edge> edges;
    edges.reserve((long long)n * (n - 1) / 2);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            edges.push_back({i, j});
        }
    }

    sort(edges.begin(), edges.end(), [&](const Edge& a, const Edge& b) {
        long long dx_a = points[a.v].x - points[a.u].x;
        long long dy_a = points[a.v].y - points[a.u].y;
        long long dx_b = points[b.v].x - points[b.u].x;
        long long dy_b = points[b.v].y - points[b.u].y;
        long long cp = dx_a * dy_b - dy_a * dx_b;
        return cp > 0; 
    });

    vector<int> pos(n);
    vector<int> cur_order(n);
    for (int i = 0; i < n; ++i) {
        pos[i] = i;
        cur_order[i] = i;
    }

    for (const auto& e : edges) {
        int u = e.u;
        int v = e.v;
        long long dx = points[v].x - points[u].x;
        long long dy = points[v].y - points[u].y;

        long long base_cross = dx * points[u].y - dy * points[u].x;
        
        long long target1 = base_cross + 2 * S;
        long long target2 = base_cross - 2 * S;

        auto check = [&](long long target) {
            int L = 0, R = n - 1;
            while (L <= R) {
                int mid = L + (R - L) / 2;
                int p_idx = cur_order[mid];
                long long val = dx * points[p_idx].y - dy * points[p_idx].x;
                if (val == target) {
                    return p_idx;
                } else if (val < target) {
                    L = mid + 1;
                } else {
                    R = mid - 1;
                }
            }
            return -1;
        };

        int w1 = check(target1);
        if (w1 != -1) {
            cout << "YES\n";
            cout << points[u].x << " " << points[u].y << "\n";
            cout << points[v].x << " " << points[v].y << "\n";
            cout << points[w1].x << " " << points[w1].y << "\n";
            return 0;
        }
        

        int w2 = check(target2);
        if (w2 != -1) {
            cout << "YES\n";
            cout << points[u].x << " " << points[u].y << "\n";
            cout << points[v].x << " " << points[v].y << "\n";
            cout << points[w2].x << " " << points[w2].y << "\n";
            return 0;
        }

        int pu = pos[u];
        int pv = pos[v];
        swap(cur_order[pu], cur_order[pv]);
        pos[u] = pv;
        pos[v] = pu;
    }

    cout << "NO\n";
}