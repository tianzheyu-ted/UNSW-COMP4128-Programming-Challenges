
#include <set>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <cassert>

using namespace std;

struct Edge {
    int from;
    int to;
    long long weight;
};

pair<long long, vector<tuple<int, int, long long>>> kruskal(int n, vector<vector<Edge>>& adj);

int main() {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges; edges.reserve(m);
    vector<vector<Edge>> adj(n + 1, vector<Edge>());

    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({u, v, w});
        adj[v].push_back({v, u, w});
        edges.push_back({u, v, w});
    }

    auto mst = kruskal(n, adj);

    set<pair<int, int>> mst_edges;
    vector<vector<Edge>> mst_adj(n + 1, vector<Edge>());
    for (auto& mst_edge : mst.second) {
        int u = get<0>(mst_edge);
        int v = get<1>(mst_edge);
        long long weight = get<2>(mst_edge);
        mst_edges.insert({u, v});
        mst_adj[u].push_back({u, v, weight});
        mst_adj[v].push_back({v, u, weight});
    }

    const int LOG = 19;
    vector<vector<int>> up(n + 1, vector<int>(LOG, 0));
    vector<vector<long long>> max_wt(n + 1, vector<long long>(LOG, 0));
    vector<int> depth(n + 1, 0);

    auto dfs_lca = [&] (auto& self, int u, int p, long long w, int d) -> void {
        depth[u] = d;
        up[u][0] = p;
        max_wt[u][0] = w;

        for (int i = 1; i < LOG; i++) {
            if (up[u][i - 1] != 0) {
                up[u][i] = up[ up[u][i - 1] ][i - 1];
                max_wt[u][i] = max(max_wt[u][i - 1], max_wt[ up[u][i - 1] ][i - 1]);
            }
        }

        for (auto& edge : mst_adj[u]) {
            if (edge.to != p) {
                self(self, edge.to, u, edge.weight, d + 1);
            }
        }
    };

    auto find_max_wt = [&] (int u, int v) {
        long long result = 0;

        if (depth[u] < depth[v]) swap(u, v);

        for (int i = LOG - 1; i >= 0; i--) {
            if (depth[u] - (1 << i) >= depth[v]) {
                result = max(result, max_wt[u][i]);
                u = up[u][i];
            }
        }

        if (u == v) return result;

        for (int i = LOG - 1; i >= 0; i--) {
            if (up[u][i] != up[v][i] && up[u][i] != 0) {
                result = max({result, max_wt[u][i], max_wt[v][i]});
                u = up[u][i];
                v = up[v][i];
            }
        }

        result = max({result, max_wt[u][0], max_wt[v][0]});
        return result;
    };

    dfs_lca(dfs_lca, 1, 0, 0, 0);

    for (auto& edge : edges) {
        if (mst_edges.count({edge.from, edge.to}) || mst_edges.count({edge.to, edge.from})) {
            cout << mst.first << '\n';
        } else {
            cout << mst.first - find_max_wt(edge.from, edge.to) + edge.weight << '\n';
        }
    }
}

struct DSU {
    vector<int> parent, size;
    DSU(int n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
        size.assign(n, 1);
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    bool unite(int i, int j) {
        int root_i = find(i), root_j = find(j);
        if (root_i != root_j) {
            if (size[root_i] < size[root_j]) swap(root_i, root_j);
            parent[root_j] = root_i;
            size[root_i] += size[root_j];
            return true;
        }
        return false;
    }
};

pair<long long, vector<tuple<int, int, long long>>> kruskal(int n, vector<vector<Edge>>& adj) {
    struct KEdge { int u, v; long long w; };
    vector<KEdge> edges;
    for (int u = 1; u <= n; ++u)
        for (auto& edge : adj[u])
            if (u < edge.to) edges.push_back({u, edge.to, edge.weight});
    
    sort(edges.begin(), edges.end(), [](const KEdge& a, const KEdge& b) {
        return a.w < b.w;
    });
    
    DSU dsu(n + 1);
    long long total_weight = 0;
    vector<tuple<int, int, long long>> mst_edges;
    for (auto& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            total_weight += e.w;
            mst_edges.push_back({e.u, e.v, e.w});
        }
    }
    return {total_weight, mst_edges};
}

