
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Edge {
    int from;
    int to;
    long long length;
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges; edges.reserve(m);
    vector<vector<Edge>> adj(n + 1, vector<Edge>());
    for (int i = 0; i < m; i++) {
        int x, y;
        long long l;
        cin >> x >> y >> l;
        adj[x].push_back({x, y, l});
        adj[y].push_back({y, x, l});
        edges.push_back({x, y, l});
    }

    vector<vector<long long>> dist(n + 1, vector<long long>(n + 1, 1e18));
    for (int i = 1; i <= n; ++i) dist[i][i] = 0;

    for (int u = 1; u <= n; ++u) {
        for (auto& edge : adj[u]) {
            dist[u][edge.to] = min(dist[u][edge.to], edge.length);
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

    vector<vector<int>> in_deg(n + 1, vector<int>(n + 1, 0));
    for (int s = 1; s <= n; s++) {
        for (auto& edge : edges) {
            if (dist[s][edge.from] + edge.length == dist[s][edge.to]) {
                in_deg[s][edge.to]++;
            }
            if (dist[s][edge.to] + edge.length == dist[s][edge.from]) {
                in_deg[s][edge.from]++;
            }
        }
    }

    for (int s = 1; s <= n; s++) {
        for (int t = s + 1; t <= n; t++) {
            int counter = 0;
            if (dist[s][t] < 1e18) {
                for (int v = 1; v <= n; v++) {
                    if (v != s) {
                        if (dist[s][v] + dist[v][t] == dist[s][t]) {
                            counter += in_deg[s][v];
                        }
                    }
                }
            }
            cout << counter << ' ';
        }
    }

    cout << '\n';
}