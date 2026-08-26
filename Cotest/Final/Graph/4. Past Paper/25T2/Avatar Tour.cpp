
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


struct Mountain {
    int nation;
    int height;
};

struct Edge {
    int from;
    int to;
    long long weight;
};

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    int c, d;
    cin >> c >> d;

    vector<Mountain> mountains(n + 2, {-1, -1});
    for (int i = 1; i <= n; i++) {
        cin >> mountains[i].height;
    }

    for (int i = 1; i <= n; i++) {
        cin >> mountains[i].nation;
    }

    vector<vector<Edge>> adj(n + 1, vector<Edge>());
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;

        Edge a_to_b, b_to_a;
        if (mountains[a].height > mountains[b].height) {
            a_to_b = {a, b, - c * (mountains[a].height - mountains[b].height)};
            b_to_a = {b, a, d * (mountains[a].height - mountains[b].height)};
        } else {
            a_to_b = {a, b, d * (mountains[b].height - mountains[a].height)};
            b_to_a = {b, a, - c * (mountains[b].height - mountains[a].height)};
        }

        adj[a].push_back(a_to_b);
        adj[b].push_back(b_to_a);
    }

    vector<vector<long long>> dist(n + 1, vector<long long>(n + 1, 1e18));
    for (int i = 1; i <= n; ++i) dist[i][i] = 0;

    for (int u = 1; u <= n; ++u) {
        for (auto& edge : adj[u]) {
            dist[u][edge.to] = min(dist[u][edge.to], edge.weight);
        }
    }

    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (dist[i][k] < 1e18 && dist[k][j] < 1e18) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    
    vector<vector<long long>> dp((1 << (k + 1)), vector<long long>(n + 1, 1e18));

    for (int i = 1; i <= n; i++) {
        int start_nation = mountains[i].nation - 1;
        dp[1 << start_nation][i] = 0;
    }

    for (int mask = 1; mask < (1 << (k + 1)); mask++) {
        for (int curr = 1; curr <= n; curr++) {
            if (dp[mask][curr] != 1e18) {
                for (int next = 1; next <= n; next++) {
                    if (next != curr) {
                        int next_mask = mask | (1 << (mountains[next].nation - 1));
                        dp[next_mask][next] = min(
                            dp[mask][curr] + dist[curr][next],
                            dp[next_mask][next]
                        );
                    }
                }
            }
        }
    }

    long long result = 1e18;
    for (auto item : dp[(1 << k) - 1]) {
        result = min(item, result);
    }

    if (result == 1e18) {
        cout << "impossible\n";
    } else {
        cout << result << '\n';
    }
}