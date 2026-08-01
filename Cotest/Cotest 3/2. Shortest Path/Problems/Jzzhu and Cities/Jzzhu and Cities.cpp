
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

struct Edge {
    int from;
    int to;
    long long length;
    char type;
};

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<Edge>> adj(1 + n, vector<Edge>());
    for (int i = 0; i < m; i++) {   
        int u, v;
        long long x;
        cin >> u >> v >> x;
        adj[u].push_back({u, v, x, 'r'});
        adj[v].push_back({v, u, x, 'r'});
    }

    for (int i = 0; i < k; i++) {
        int s;
        long long y;
        cin >> s >> y;
        adj[1].push_back({1, s, y, 't'});
        adj[s].push_back({s, 1, y, 't'});
    }

    vector<bool> train_used(1 + n, false);
    vector<long long> dist(1 + n, 1e18);
    auto dijkstra = [&] (int start) -> void {
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        dist[start] = 0;
        pq.push({0, start});
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dist[u]) continue;
            for (auto& edge : adj[u]) {
                int v = edge.to;
                if (dist[u] + edge.length < dist[v]) {
                    dist[v] = dist[u] + edge.length;
                    if (edge.type == 't') {
                        train_used[v] = true;
                    } else {
                        train_used[v] = false;
                    }
                    pq.push({dist[v], v});
                } else if (dist[u] + edge.length == dist[v]) {
                    if (edge.type == 'r') {
                        train_used[v] = false;
                    }
                }
            }
        }
    };

    dijkstra(1);

    int counter = 0;
    for (int i = 2; i <= n; i++) {
        if (train_used[i]) {
            counter++;
        }
    }

    cout << k - counter << '\n';
}