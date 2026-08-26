
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

struct Edge {
    int id;
    int from;
    int to;
    bool erased;
};

int main() {
    int n, m, s, t;
    long long l;
    cin >> n >> m >> l >> s >> t;

    vector<Edge> edges;
    edges.reserve(m);

    vector<int> erased_edges;
    erased_edges.reserve(m);

    vector<long long> weights(m, -1);
    vector<vector<Edge>> adj(n, vector<Edge>());
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        
        if (w == 0) {
            weights[i] = 1;
            erased_edges.push_back(i);
        } else {
            weights[i] = w;
        }

        adj[u].push_back({i, u, v, (w == 0)});
        adj[v].push_back({i, v, u, (w == 0)});
        edges.push_back({i, u, v, (w == 0)});
    }

    auto dijkstra = [] (int s, int t, vector<long long>& weights, vector<long long>& distances, vector<vector<Edge>>& adj) -> void {
        fill(distances.begin(), distances.end(), 1e18);
        distances[s] = 0;

        priority_queue<pair<long long, int>,  vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        pq.push({0, s});

        while (pq.size() > 0) {
            auto curr = pq.top();
            pq.pop();

            if (curr.first > distances[curr.second]) continue;

            for (auto edge : adj[curr.second]) {
                long long weight = weights[edge.id];
                if (curr.first + weight < distances[edge.to]) {
                    distances[edge.to] = curr.first + weight;
                    pq.push({curr.first + weight, edge.to});
                }
            }
        }
    };

    vector<long long> dist1(n, 1e18);
    dijkstra(s, t, weights, dist1, adj);

    for (auto id : erased_edges) {
        weights[id] = 1e18;
    }

    vector<long long> dist2(n, 1e18);
    dijkstra(s, t, weights, dist2, adj);

    if (dist1[t] > l || dist2[t] < l) {
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n";

    if (dist2[t] != l) {
        int key = -1;
        for (int i = 0; i < erased_edges.size(); i++) {
            int id = erased_edges[i];
            weights[id] = 1;
            dijkstra(s, t, weights, dist2, adj);
            if (dist2[t] <= l) {
                key = i;
                break;
            }
        }
        weights[erased_edges[key]] = 1 + l - dist2[t];
    }
    
    for (auto edge : edges) {
        cout << edge.from << ' ' << edge.to << ' ' << weights[edge.id] << '\n';
    }
}