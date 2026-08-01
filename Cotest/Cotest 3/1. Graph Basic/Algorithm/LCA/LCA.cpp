
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

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

    

    auto lca = [] (int x, int y, vector<vector<int>>& adj) -> int {
        int n = adj.size();
        const int LOG = 19;
        vector<vector<int>> up(n, vector<int>(LOG, 0));
        vector<vector<long long>> max_wt(n, vector<long long>(LOG, 0));
        vector<int> depths(n, 0);

        auto dfs_lca = [&] (auto& self, int u, int parent, int depth) -> void {
            depths[u] = depth;
            up[u][0] = parent;
            for (int i = 1; i < LOG; i++) {
                if (up[u][i - 1] != 0) {
                    up[u][i] = up[ up[u][i - 1] ][i - 1];
                }
            }
            for (auto next : adj[u]) {
                if (next != parent) {
                    self(self, next, u, depth + 1);
                }
            }
        };

        dfs_lca(dfs_lca, 1, 0, 0);

        if (x == y) return x;
        if (depths[x] < depths[y]) swap(x, y);
        for (int i = LOG - 1; i >= 0; i--) {
            if (depths[x] - (1 << i) >= depths[y]) {
                x = up[x][i];
            }
        }

        if (x == y) return x;
        for (int i = LOG - 1; i >= 0; i--) {
            if (up[x][i] != 0 && up[x][i] != up[y][i]) {
                x = up[x][i];
                y = up[y][i];
            }
        }

        return up[x][0];
    };

    
    int x, y;
    while (cin >> x >> y) {
        cout << "LCA: " << lca(x, y, adj) << '\n';
    }
}