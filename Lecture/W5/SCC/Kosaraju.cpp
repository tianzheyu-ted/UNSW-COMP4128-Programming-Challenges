
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n, e;
    cin >> n >> e;

    vector<vector<int>> adj(n + 1, vector<int>());
    vector<vector<int>> rev_adj(n + 1, vector<int>());
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        rev_adj[v].push_back(u);
    }

    // --- Kosaraju 1 Step: Obtain topological order ---
    vector<bool> visited(n + 1, false);
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

    for (int i = 1; i < n + 1; i++) {
        if (!visited[i]) {
            dfs1(dfs1, i);
        }
    }

    reverse(order.begin(), order.end());

    // --- Kosaraju 2 Step: Extract strongly connected components ---
    int scc_counter = 0;

    vector<int> scc(n + 1, 0);
    vector<bool> visited2(n + 1, false);
    
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

    for (int i = 1; i <= n; i++) {
        cout << i << ": " << scc[i] << '\n';
    }



    vector<set<int>> dag_adj(scc_counter + 1);
    vector<int> dag_in_degree(scc_counter + 1, 0);
    for (int u = 1; u <= n; u++) {
        for (int v : adj[u]) {
            if (scc[u] != scc[v]) {
                dag_adj[scc[u]].insert(scc[v]);
                dag_in_degree[scc[v]]++;
            }
        }
    }
}
