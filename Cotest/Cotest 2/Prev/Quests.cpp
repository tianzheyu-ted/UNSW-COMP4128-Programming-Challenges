
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

bool check(vector<long long>& a, long long c, int k, int d);

int main() {
    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int n, d;
        long long c;
        cin >> n >> c >> d;

        vector<long long> a(n, -1);
        for (int j = 0; j < n; j++) {
            cin >> a[j];
        }

        sort(a.begin(), a.end(), [] (auto x, auto y) {
            return x > y;
        });

        int lo = 0;
        int hi = d - 1;

        if (!check(a, c, lo, d)) {
            cout << "Impossible\n";
            continue;
        }

        if (check(a, c, hi, d)) {
            cout << "Infinity\n";
            continue;
        }

        while (lo < hi) {
            int mid = lo + (hi - lo + 1) / 2;
            if (check(a, c, mid, d)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }

        cout << lo << '\n';
    }
}


bool check(vector<long long>& a, long long c, int k, int d) {
    long long sum = 0;
    for (int i = 0; i < d; i++) {
        if (i % (k + 1) < a.size()) {
            sum += a[i % (k + 1)];
        }
    }
    return sum >= c;
}