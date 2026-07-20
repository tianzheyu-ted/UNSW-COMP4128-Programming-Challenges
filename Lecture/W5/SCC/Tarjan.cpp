
#include <stack>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    int n, e;
    cin >> n >> e;

    vector<vector<int>> adj(n + 1, vector<int>());
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    int timer = 0;
    int scc_counter = 0;
    vector<int> dfn(n + 1, 0);
    vector<int> low(n + 1, 0);
    vector<int> scc(n + 1, 0);

    stack<int> st;
    vector<bool> in_stack(n + 1, false);

    auto tarjan = [&] (auto& self, int u) -> void {
        timer++;
        dfn[u] = timer;
        low[u] = timer;

        for (auto v : adj[u]) {
            if (!dfn[v]) {
                self(self, v);
                low[u] = min(low[u], low[v]);
            } else {
                if (in_stack[v]) {
                    low[u] = min(low[u], dfn[v]);
                }
            }
        }

        if (dfn[u] == low[u]) {
            scc_counter++;
            while (true) {
                int node = st.top();
                st.pop();
                in_stack[node] = false;
                scc[node] = scc_counter;
                if (node == u) break;
            }
        }
    };

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(tarjan, i);
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << "Node " << i << " belongs to SCC " << scc[i] << '\n';
    }
}