
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, w;
};

int main() {
    int n;
    cin >> n;

    vector<long long> X;

    vector<pair<long long, long long>> segments(n, {-1, -1});
    for (int i = 0; i < n; i++) {
        long long a, b, h;
        cin >> a >> b >> h;
        segments[i] = {a, b};
        X.push_back(a);
        X.push_back(b);
    }

    sort(X.begin(), X.end());
    X.erase(unique(X.begin(), X.end()), X.end());
    int m = X.size();

    vector<pair<int, int>> comp_segments(n);
    for (int i = 0; i < n; i++) {
        int L = lower_bound(X.begin(), X.end(), segments[i].first) - X.begin();
        int R = lower_bound(X.begin(), X.end(), segments[i].second) - X.begin();
        comp_segments[i] = {L, R};
    }

    auto check = [&] (int k) -> bool {
        vector<Edge> edges;
        for (int i = 1; i < m; i++) {
            edges.push_back({i, i - 1, 0});
            edges.push_back({i - 1, i , 1});
        }

        for (auto& seg: comp_segments) {
            int l = seg.first;
            int r = seg.second;
            edges.push_back({r, l, -1});
            edges.push_back({l, r, k});
        }

        vector<int> dist(m, 0);
        for (int i = 0; i < m; i++) {
            bool relaxed = false;
            for (auto& edge : edges) {
                if (dist[edge.u] + edge.w < dist[edge.v]) {
                    if (i == m - 1) return false;
                    dist[edge.v] = dist[edge.u] + edge.w;
                    relaxed = true;
                }
            }
            if (!relaxed) break;
        }
        return true;
    };

    int lo = 1;
    int hi = n;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (check(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    cout << lo << '\n';
}