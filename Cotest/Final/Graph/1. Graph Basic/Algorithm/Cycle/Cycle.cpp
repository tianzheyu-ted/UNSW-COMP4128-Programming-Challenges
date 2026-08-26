
#include <vector>
#include <iostream>

using namespace std;

struct DSU {
    vector<int> parent;
    DSU (int n) {
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
    int n, e;
    cin >> n >> e;

    vector<vector<int>> adj(n + 1, vector<int>());
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto has_cycle_dfs = [] (vector<vector<int>>& adj) -> bool {
        int n = adj.size();
        vector<bool> visited(n, false);
        auto dfs = [&](auto& self, int curr, int parent) -> bool {
            visited[curr] = true;
            for (int next : adj[curr]) {
                if (!visited[next]) {
                    if (self(self, next, curr)) return true;
                } else if (next != parent) {
                    return true;
                }
            }
            return false;
        };
        for (int i = 0; i <= n; i++) {
            if (!visited[i] && !adj[i].empty()) { 
                if (dfs(dfs, i, -1)) {
                    return true;
                }
            }
        }
        return false;
    };

    auto has_cycle = [] (const vector<vector<int>>& adj) -> bool {
        int n = adj.size();
        DSU dsu(n);
        for (int u = 0; u <= n; u++) {
            for (int v : adj[u]) {
                if (u <= v) {
                    if (!dsu.unite(u, v)) {
                        return true;
                    }
                }
            }
        }
        return false;
    };

    cout << (has_cycle(adj) ? "true" : "false") << '\n';
}