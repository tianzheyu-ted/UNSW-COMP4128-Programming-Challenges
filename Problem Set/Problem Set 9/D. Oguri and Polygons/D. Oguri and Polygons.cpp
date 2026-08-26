#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

struct Point {
    long long x, y;
};

const int MAX_M = 100005;
const int MAX_N = 45;

bitset<MAX_M> right_of[MAX_N][MAX_N];
int tri_count[MAX_N][MAX_N][MAX_N];

inline long long cross_product(const Point& O, const Point& U, const Point& V) {
    return (U.x - O.x) * (V.y - O.y) - (U.y - O.y) * (V.x - O.x);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<Point> red(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> red[i].x >> red[i].y;
    }

    vector<Point> black(m + 1);
    for (int i = 1; i <= m; i++) {
        cin >> black[i].x >> black[i].y;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            for (int p = 1; p <= m; p++) {
                if (cross_product(red[i], red[j], black[p]) < 0) {
                    right_of[i][j].set(p);
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                if (i == j || j == k || i == k) continue;
                if (cross_product(red[i], red[j], red[k]) < 0) {
                    tri_count[i][j][k] = (right_of[i][j] & right_of[j][k] & right_of[k][i]).count();
                }
            }
        }
    }

    int q;
    cin >> q;
    vector<int> v(MAX_N); 
    
    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            cin >> v[j];
        }

        int ans = 0;
        for (int j = 1; j < k - 1; j++) {
            ans += tri_count[v[0]][v[j]][v[j + 1]];
        }
        
        cout << ans << '\n';
    }

    return 0;
}



int main2() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<Point> red_points(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> red_points[i].x >> red_points[i].y;
    }

    vector<Point> black_points(m + 1);
    for (int i = 1; i <= m; i++) {
        cin >> black_points[i].x >> black_points[i].y;
    }

    auto cross_product = [] (Point O, Point U, Point V) -> long long {
        return (U.x - O.x) * (V.y - O.y) - (U.y - O.y) * (V.x - O.x);
    };

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            for (int p = 1; p <= m; p++) {
                if (cross_product(red_points[i], red_points[j], black_points[p]) < 0) {
                    right_of[i][j].set(p);
                }
            }
        }
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        vector<int> v(k);
        for (int j = 0; j < k; j++) {
            cin >> v[j];
        }

        // bitset<MAX_M> inside = right_of[v[k - 1]][v[0]];

        for (int j = 0; j < k - 1; j++) {
        //     inside &= right_of[v[j]][v[j + 1]];
        }

        // cout << inside.count() << '\n';
    }
}