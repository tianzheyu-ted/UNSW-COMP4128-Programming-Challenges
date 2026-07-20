
#include <set>
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    for (int test = 0; test < t; test++) {
        int n;
        cin >> n;

        vector<vector<int>> grid(3, vector<int>(n));
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < n; j++) {
                cin >> grid[i][j];
            }
        }

        vector<set<int>> adj(2 * n + 1);
        vector<set<int>> rev_adj(2 * n + 1);

        auto get_id = [&] (int val) {
            if (val > 0) return val;
            return abs(val) + n;
        };

        auto add_condition = [&] (int u, int v) {
            int not_u = get_id(-u), true_v = get_id(v);
            int not_v = get_id(-v), true_u = get_id(u);
    
            // ~u -> v
            adj[not_u].insert(true_v);
            // ~v -> u
            adj[not_v].insert(true_u);

            rev_adj[true_v].insert(not_u);
            rev_adj[true_u].insert(not_v);
        };

        for (int i = 0; i < n; i++) {
            int x = grid[0][i];
            int y = grid[1][i];
            int z = grid[2][i];

            add_condition(x, y);
            add_condition(y, z);
            add_condition(x, z);
        }

        // --- Kosaraju 1 Step: Obtain topological order ---

        vector<bool> visited(2 * n + 1, false);
        vector<int> order;
        
        auto dfs1 = [&](auto& self, int u) -> void {
            visited[u] = true;
            for (int v : adj[u]) {
                if (!visited[v]) {
                    self(self, v);
                }
            }
            order.push_back(u);
        };

        for (int i = 1; i < 2 * n + 1; i++) {
            if (!visited[i]) {
                dfs1(dfs1, i);
            }
        }

        reverse(order.begin(), order.end());

        // --- Kosaraju 2 Step: Extract strongly connected components ---
        int scc_counter = 0;
        vector<int> scc(2 * n + 1, 0);
        vector<bool> visited2(2 * n + 1, false);
        
        auto dfs2 = [&](auto& self, int u) -> void {
            visited2[u] = true;
            scc[u] = scc_counter;
            for (int v : rev_adj[u]) {
                if (!visited2[v]) {
                    self(self, v);
                }
            }
        };

        for (auto u : order) {
            if (!visited2[u]) {
                scc_counter++;
                dfs2(dfs2, u);
            }
        }


        bool possible = true;
        for (int i = 1; i <= n; i++) {
            if (scc[i] == scc[i + n]) {
                possible = false;
                break;
            }
        }

        if (possible) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}

