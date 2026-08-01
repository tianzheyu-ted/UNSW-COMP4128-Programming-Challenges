
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

struct Edge {
    int from;
    int to;
    int color;
    long long weight;
};

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> h(n + 1, -1);
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    vector<vector<Edge>> adj(n + 1, vector<Edge>());
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;

        int a_to_b = 0;
        int b_to_a = 0;
        if (h[a] < h[b]) {
            a_to_b = h[b] - h[a];
        }

        if (h[b] < h[a]) {
            b_to_a = h[a] - h[b];
        }

        adj[a].push_back({a, b, c, (long long)a_to_b});
        adj[b].push_back({b, a, c, (long long)b_to_a});
    }

    // auto dijkstra = [&] (int start, vector<vector<Edge>>& adj) -> vector<long long> {
    //     vector<long long> dist(n, 1e18);
    //     priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    //     dist[start] = 0;
    //     pq.push({0, start});
    //     while (!pq.empty()) {
    //         auto [d, u] = pq.top(); pq.pop();
    //         if (d > dist[u]) continue;
    //         for (auto& edge : adj[u]) {
    //             int v = edge.to;
    //             if (dist[u] + edge.weight < dist[v]) {
    //                 dist[v] = dist[u] + edge.weight;
    //                 pq.push({dist[v], v});
    //             }
    //         }
    //     }
    //     return dist;
    // };

    // auto src_dist = dijkstra(1, adj);
    // auto dest_dist = dijkstra(n, adj);
    
    vector<vector<long long>> dp((1 << (k + 1)), vector<long long>(n + 1, 1e18));

    // {weight, curr, color}
    priority_queue<tuple<long long, int, int>, 
                   vector<tuple<long long, int, int>>, 
                   greater<tuple<long long, int, int>>> pq;

    dp[0][1] = 0;
    pq.push({0, 1, 0});
    while (!pq.empty()) {
        auto [cost, curr, mask] = pq.top(); pq.pop();
        if (cost > dp[mask][curr]) continue;
        if (curr == n && mask== (1 << k) - 1) {
            cout << dp[mask][curr] << '\n';
            return 0;
        }

        for (auto& edge : adj[curr]) {
            int next = edge.to;
            int next_mask = mask | (1 << (edge.color - 1));
            if (dp[mask][curr] + edge.weight < dp[next_mask][next]) {
                dp[next_mask][next] =  dp[mask][curr] + edge.weight;
                pq.push({dp[next_mask][next], next, next_mask});
            }
        }
    }

    cout << -1 << '\n';
}