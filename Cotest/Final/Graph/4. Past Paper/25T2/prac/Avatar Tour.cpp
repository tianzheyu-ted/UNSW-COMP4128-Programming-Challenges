
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

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

    vector<int> heights(n + 1, -1);
    for (int i = 1; i <= n; i++) {
        cin >> heights[i];
    }

    vector<int> nations(n + 1, -1);
    for (int i = 1; i <= n; i++) {
        cin >> nations[i];
    }

    vector<vector<Edge>> adj(n + 1, vector<Edge>());
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        long long a_to_b = 0;
        long long b_to_a = 0;
        if (heights[a] > heights[b]) {
            a_to_b = - c * (heights[a] - heights[b]);
            b_to_a = d * (heights[a] - heights[b]);
        } else if (heights[b] > heights[a]) {
            a_to_b = d * (heights[b] - heights[a]);
            b_to_a = - c * (heights[b] - heights[a]);
        }
        adj[a].push_back({a, b, a_to_b});
        adj[b].push_back({b, a, b_to_a});
    }

    auto floyd_warshall = [] (const vector<vector<Edge>>& adj) -> tuple<bool, vector<vector<long long>>, vector<vector<int>>> {
        int n = adj.size();
        const long long INF = 1e18;
        vector<vector<long long>> dist(n, vector<long long>(n, INF));
        vector<vector<int>> nxt(n, vector<int>(n, -1)); 
        for (int i = 0; i < n; ++i) {
            dist[i][i] = 0;
            for (const auto& edge : adj[i]) {
                int u = i;
                int v = edge.to;
                long long w = edge.weight;
                if (w < dist[u][v]) {
                    dist[u][v] = w;
                    nxt[u][v] = v;
                }
            }
        }
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                if (dist[i][k] == INF) continue; 
                for (int j = 0; j < n; ++j) {
                    if (dist[k][j] == INF) continue;                
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        nxt[i][j] = nxt[i][k]; 
                    }
                }
            }
        }
        bool has_negative_cycle = false;
        for (int i = 0; i < n; ++i) {
            if (dist[i][i] < 0) {
                has_negative_cycle = true;
                break;
            }
        }
        return {has_negative_cycle, dist, nxt};
    };

    auto [has_negative_cycle, dist, nxt] = floyd_warshall(adj);

    vector<vector<long long>> dp((1 << (k + 1)), vector<long long>(n + 1, 1e18));
    for (int i = 1; i <= n; i++) {
        dp[1 << (nations[i] - 1)][i] = 0;
    }

    for (int mask = 1; mask < 1 << (k + 1); mask++) {
        for (int curr = 1; curr <= n; curr++) {
            for (int next = 1; next <= n; next++) {
                if (next != curr) {
                    int next_mask = mask | (1 << (nations[next] - 1));
                    dp[next_mask][next] = min(dp[mask][curr] + dist[curr][next], dp[next_mask][next]);
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