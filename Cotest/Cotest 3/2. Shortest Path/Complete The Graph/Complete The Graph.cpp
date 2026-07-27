
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

struct Edge {
    int id;
    int from;
    int to;
    long long weight;
};

int main() {
    int n, m, s, t;
    long long l;
    cin >> n >> m >> l >> s >> t;

    vector<Edge> edges(m, {-1, -1, -1, -1});
    vector<pair<Edge&, Edge&>> erased_edges;
    erased_edges.reserve(m);

    vector<vector<Edge>> base_adj(n, vector<Edge>());
    for (auto& item : base_adj) {
        item.reserve(m);
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        long long weight;
        cin >> u >> v >> weight;
        base_adj[u].push_back({i, u, v, weight});
        base_adj[v].push_back({i, v, u, weight});
        edges[i] = {i, u, v, weight};

        if (weight == 0) {
            erased_edges.push_back({
                base_adj[u][base_adj[u].size() - 1],
                base_adj[v][base_adj[v].size() - 1]
            });
        }
    }

    auto dijkstra = [&] (int start, vector<vector<Edge>>& adj) -> vector<long long> {
        vector<long long> dist(n, 1e18);
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        dist[start] = 0;
        pq.push({0, start});
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dist[u]) continue;
            for (auto& edge : adj[u]) {
                int v = edge.to;
                if (dist[u] + edge.weight < dist[v]) {
                    dist[v] = dist[u] + edge.weight;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    };

    auto complete = [&] (int x) -> void {
        for (int i = 0; i < erased_edges.size(); i++) {
            if (i < x) {
                erased_edges[i].first.weight = 1e9;
                erased_edges[i].second.weight = 1e9;
                edges[erased_edges[i].first.id].weight = 1e9;
            } else {
                erased_edges[i].first.weight = 1;
                erased_edges[i].second.weight = 1;
                edges[erased_edges[i].first.id].weight = 1;
            }
        }
    };

    auto check = [&] (int x) -> long long {
        vector<long long> dist;
        complete(x);
        dist = dijkstra(s, base_adj);
        return dist[t];
    };
    
    int lo = 0;
    if (check(lo) > l) {
        cout << "NO\n";
        return 0;
    }

    int hi = erased_edges.size();
    if (check(hi) < l) {
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n";
    
    // check(lo) <= l <= check(hi)
    // find first value such that check(mid) > l
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (check(mid) > l) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    int key = lo;
    long long diff = l - check(key - 1);

    if (key - 1 >= 0) {
        erased_edges[key - 1].first.weight = diff;
        erased_edges[key - 1].second.weight = diff;
        edges[erased_edges[key - 1].first.id].weight += diff;
    }
    

    for (auto edge : edges) {
        cout << edge.from << ' ' << edge.to << ' ' << edge.weight << '\n';
    }
}