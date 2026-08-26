
#include <set>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<vector<int>> adj(n + 1, vector<int>());
    vector<vector<int>> rev_adj(n + 1, vector<int>());
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        adj[i].push_back(a);
        adj[i].push_back(b);
        rev_adj[a].push_back(i);
        rev_adj[b].push_back(i);
    }

    // scc number starts from 1
    auto kosaraju = [&] () -> pair<int, vector<int>> {
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
        return {scc_counter, scc};
    };

    pair<int, vector<int>> kosaraju_result = kosaraju();

    vector<set<int>> dag_adj(kosaraju_result.first + 1, set<int>());
    for (int i = 1; i <= n; i++) {
        int scc = kosaraju_result.second[i];
        for (auto neighbor : adj[i]) {
            int neighbor_scc = kosaraju_result.second[neighbor];
            if (scc != neighbor_scc) {
                dag_adj[scc].insert(neighbor_scc);
            }
        }
    }

    auto topological_sort = [] (vector<set<int>> adj, int n) -> vector<int> {
        vector<int> in_degree(n, 0), order;
        for (int u = 1; u < n; ++u)
            for (auto& edge : adj[u]) in_degree[edge]++;
        queue<int> q;
        for (int i = 1; i < n; ++i)
            if (in_degree[i] == 0) q.push(i);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            order.push_back(u);
            for (auto& edge : adj[u])
                if (--in_degree[edge] == 0) q.push(edge);
        }
        return order;
    };

    vector<int> topological_order = topological_sort(dag_adj, kosaraju_result.first + 1);

    int prev = -1;
    bool first = true;
    for (auto& item : topological_order) {
        if (first) {
            if (item != kosaraju_result.second[1]) {
                cout << "NO\n";
                return 0;
            }
            first = false;
            prev = kosaraju_result.second[1];
        } else {
            if (dag_adj[prev].count(item) == 0) {
                cout << "NO\n";
                return 0;
            }
            prev = item;
        }
    }

    cout << "YES\n";
}