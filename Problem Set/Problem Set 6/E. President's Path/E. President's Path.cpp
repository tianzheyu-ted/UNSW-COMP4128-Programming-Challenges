
#include <queue>
#include <bitset>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Edge {
    int from;
    int to;
    int length;
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m, {-1, -1, -1});
    vector<vector<Edge>> adj(n + 1, vector<Edge>());
    for (int i = 0; i < m; i++) {
        int x, y, l;
        cin >> x >> y >> l;
        adj[x].push_back({x, y, l});
        adj[y].push_back({y, x, l});
        edges[i] = {x, y, l};
    }

    auto dijkstra = [&] (int s, vector<int>& dist) -> void {
        fill(dist.begin(), dist.end(), 1e9);
        dist[s] = 0;

        // {distance, vertex}
        priority_queue<pair<int, int>,  vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, s});

        while (pq.size() > 0) {
            auto curr = pq.top();
            pq.pop();
            if (curr.first > dist[curr.second]) continue;
            for (auto edge : adj[curr.second]) {
                if (curr.first + edge.length < dist[edge.to]) {
                    dist[edge.to] = curr.first + edge.length;
                    pq.push({curr.first + edge.length, edge.to});
                }
            }
        }
    };

    vector<vector<int>> dist(n + 1, vector<int>(n + 1, -1));
    for (int i = 1; i <= n; i++) {
        dijkstra(i, dist[i]);
    }

    vector<vector<int>> ans(n + 1, vector<int>(n + 1, 0));

    for (int s = 0; s <= n; s++) {
        vector<int> order(n);
        for (int i = 0; i < n; i++) {
            order[i] = i + 1;
        }

        sort(order.begin(), order.end(), [&](int a, int b) {
            return dist[s][a] < dist[s][b];
        });

        vector<bitset<505>> mask(n + 1);
        vector<int> in_degree(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            mask[i].set(i);
        }

        for (int u : order) {
            if (dist[s][u] == 1e9) continue; 
            for (auto& edge : adj[u]) {
                int v = edge.to;
                if (dist[s][u] + edge.length == dist[s][v]) {
                    mask[v] |= mask[u];
                    in_degree[v]++;
                }
            }
        }

        for (int t = s + 1; t <= n; t++) {
            if (dist[s][t] == 1e9) {
                ans[s][t] = 0;
                continue;
            }
            int edge_count = 0;
            for (int k = 1; k <= n; k++) {
                if (k != s && mask[t].test(k)) {
                    edge_count += in_degree[k];
                }
            }
            ans[s][t] = edge_count;
        }
    }

    for (int s = 1; s <= n; s++) {
        for (int t = s + 1; t <= n; t++) {
            cout << ans[s][t] << " ";
        }
    }
    cout << "\n";
}