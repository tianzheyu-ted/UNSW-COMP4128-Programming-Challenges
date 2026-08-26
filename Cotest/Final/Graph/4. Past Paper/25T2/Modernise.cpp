
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <numeric>

using namespace std;

struct Edge {
    int from;
    int to;
    long long length;
};

pair<long long, vector<tuple<int, int, long long>>> kruskal(int n, vector<vector<Edge>>& adj);

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

    auto mst = kruskal(n, adj);

    long long max_weigth = 0;
    for (auto edge : mst.second) {
        max_weigth = max(get<2>(edge), max_weigth);
    }

    cout << mst.first - max_weigth << '\n';
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
            if (u < edge.to) edges.push_back({u, edge.to, edge.length});
    
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