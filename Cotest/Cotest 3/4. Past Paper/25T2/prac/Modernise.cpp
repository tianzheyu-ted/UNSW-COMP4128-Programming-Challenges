
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Edge {
    int from;
    int to;
    long long weight;
};

struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i; 
        }
    }
    int find(int i) {
        if (parent[i] == i) {
            return i;
        }
        return parent[i] = find(parent[i]); 
    }
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j; 
            return true; 
        }
        return false; 
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<Edge>> adj(n + 1, vector<Edge>());
    for (int i = 0; i < m; i++) {
        int a, b, l;
        cin >> a >> b >> l;
        adj[a].push_back({a, b, l});
        adj[b].push_back({b, a, l});
    }

    auto kruskal = [] (vector<vector<Edge>>& adj) -> pair<long long, vector<tuple<int, int, long long>>> {
        int n = adj.size();
        struct KEdge { int u, v; long long w; };
        vector<KEdge> edges;
        for (int u = 0; u < n; ++u) {
            for (const auto& edge : adj[u]) {
                if (u < edge.to) {
                    edges.push_back({u, edge.to, edge.weight});
                }
            }
        }
        sort(edges.begin(), edges.end(), [](const KEdge& a, const KEdge& b) {
            return a.w < b.w;
        });
        DSU dsu(n);
        long long total_weight = 0;
        vector<tuple<int, int, long long>> mst_edges;
        for (auto& e : edges) {
            if (dsu.unite(e.u, e.v)) {
                total_weight += e.w;
                mst_edges.push_back({e.u, e.v, e.w});
            }
        }
        return {total_weight, mst_edges};
    };

    auto [total_weight, mst] = kruskal(adj);

    long long max_weight = 0;
    for (auto edge : mst) {
        max_weight = max(get<2>(edge), max_weight);
    }

    cout << total_weight - max_weight << '\n';
}