
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

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

struct Edge {
    int id;
    int u;
    int v;
    long long weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges;
    vector<set<pair<int, long long>>> adj(n + 1, set<pair<int, long long>>());

    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].insert({v, w});
        adj[v].insert({u, w});
        edges.push_back({i, u, v, w});
    }

    int edge_counter = 0;
    long long mst_weight = 0;
    set<Edge> mst_edges;
    vector<set<pair<int, long long>>> mst_adj(n + 1, set<pair<int, long long>>());

    auto dfs = [&] (auto& self, int u, int p, vector<set<pair<int, long long>>>& adj, vector<bool>& visited) {
        if (visited[u]) {
            return u != p;
        } else {
            visited[u] = true;
            for (auto edge : adj[u]) {
                int v = edge.first;
                if (self(self, v, u, adj, visited)) {
                    return true;
                }
            }
            return false;
        }
    };

    auto has_cycle_dfs = [&] (vector<set<pair<int, long long>>>& mst_adj) {
        for (int i = 1; i <= n; i++) {
            vector<bool> visited(n + 1, false);
            if (dfs(dfs, i, 0, mst_adj, visited)) {
                return true;
            }
        }
        return false;
    };

    DSU dsu(n);
    vector<Edge> sorted_edges = edges;
    sort(sorted_edges.begin(), sorted_edges.end());

    vector<bool> in_mst(m, false);

    for (auto edge : sorted_edges) {
        if (dsu.unite(edge.u, edge.v)) {
            edge_counter++;
            mst_edges.insert(edge);
            in_mst[edge.id] = true;
            mst_weight += edge.weight;
            mst_adj[edge.u].insert({edge.v, edge.weight});
            mst_adj[edge.v].insert({edge.u, edge.weight});
            if (edge_counter == n - 1) break;
        }
    }
    


    const int LOG = 19;
    vector<vector<int>> up(n + 1, vector<int>(LOG, 0));
    vector<vector<long long>> max_wt(n + 1, vector<long long>(LOG, 0));
    vector<int> depth(n + 1, 0);

    auto dfs_lca = [&](auto& self, int u, int p, long long w, int d) -> void {
        depth[u] = d;
        up[u][0] = p;
        max_wt[u][0] = w;
        
        for (int i = 1; i < LOG; i++) {
            if (up[u][i - 1] != 0) {
                up[u][i] = up[ up[u][i - 1] ][i - 1];
                max_wt[u][i] = max(max_wt[u][i - 1], max_wt[ up[u][i - 1] ][i - 1]);
            }
        }
    
        for (auto edge : mst_adj[u]) {
            int v = edge.first;
            long long weight = edge.second;
            if (v != p) {
                self(self, v, u, weight, d + 1);
            }
        }
    };

    dfs_lca(dfs_lca, 1, 0, 0, 0);

    auto get_max_edge = [&](int u, int v) -> long long {
        long long ans = 0;
        if (depth[u] < depth[v]) {
            swap(u, v);
        }
        for (int i = LOG - 1; i >= 0; i--) {
            if (depth[u] - (1 << i) >= depth[v]) {
                ans = max(ans, max_wt[u][i]);
                u = up[u][i];
            }
        }
        if (u == v) {
            return ans;
        }
        for (int i = LOG - 1; i >= 0; i--) {
            if (up[u][i] != 0 && up[u][i] != up[v][i]) {
                ans = max({ans, max_wt[u][i], max_wt[v][i]});
                u = up[u][i];
                v = up[v][i];
            }
        }
        ans = max({ans, max_wt[u][0], max_wt[v][0]});
        return ans;
    };


    for (auto edge : edges) {
        if (in_mst[edge.id]) {
            cout << mst_weight << '\n';
        } else {
            cout << mst_weight - get_max_edge(edge.u, edge.v) + edge.weight << '\n';
        }
    }
}


