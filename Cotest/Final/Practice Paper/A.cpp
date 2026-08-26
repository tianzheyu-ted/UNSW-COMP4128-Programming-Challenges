
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

auto kosaraju = [] (vector<vector<int>>& adj, vector<vector<int>>& rev_adj) -> pair<int, vector<int>> {
    // --- Kosaraju 1 Step: Obtain topological order ---
    int n = adj.size();
    vector<bool> visited(n, false);
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
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs1(dfs1, i);
        }
    }
    reverse(order.begin(), order.end());

    // --- Kosaraju 2 Step: Extract strongly connected components ---
    int scc_counter = 0;
    vector<int> scc(n, 0);
    vector<bool> visited2(n, false);
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
    return {scc_counter, scc};
};

int main() {
    int n, k;

    cin >> n >> k;

    // out: [0, n - 1]
    // in:  [n, 2*n - 1]
    vector<vector<int>> adj(2*n, vector<int>());
    vector<vector<int>> rev_adj(2*n, vector<int>());
    for (int i = 0; i < n; i++) {
        int curr_out = i;
        int curr_in = i + n;
        int next_out = (1LL * k * i) % n;
        int next_in = next_out + n;

        adj[curr_out].push_back(next_in);
        rev_adj[next_in].push_back(curr_out);

        adj[curr_in].push_back(curr_out);
        rev_adj[curr_out].push_back(curr_in);
    }

    auto scc = kosaraju(adj, rev_adj);

    for (int i = 0; i < n; i++) {
        if (scc.second[i] != scc.second[i + n]) {
            cout << "INVALID\n";
            return 0;
        }
    }

    cout << "VALID\n";
}