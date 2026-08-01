
#include <stack>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;

        vector<vector<int>> g(3, vector<int>(n, -1));
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < n; k++) {
                cin >> g[j][k];
            }
        }

        const int TRUE_BASE = 0;
        const int FALSE_BASE = n;
        vector<vector<int>> adj(2*n, vector<int>());

        auto get_node = [&](int x) {
            if (x > 0) return x - 1;
            return -x - 1 + n;
        };

        auto get_neg = [&](int x) {
            return get_node(-x);
        };

        for (int i = 0; i < n; i++) {
            int a = g[0][i];
            int b = g[1][i];
            int c = g[2][i];
            adj[get_neg(a)].push_back(get_node(b));
            adj[get_neg(b)].push_back(get_node(a));

            adj[get_neg(a)].push_back(get_node(c));
            adj[get_neg(c)].push_back(get_node(a));

            adj[get_neg(c)].push_back(get_node(b));
            adj[get_neg(b)].push_back(get_node(c));
        }

        int timer = 0;
        int scc_counter = 0;
        vector<int> dfn(2*n, 0);
        vector<int> low(2*n, 0);
        vector<int> scc(2*n, 0);

        stack<int> st;
        vector<bool> in_stack(2*n, false);

        auto tarjan = [&] (auto& self, int u) -> void {
            st.push(u);
            in_stack[u] = true;

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

        for (int i = 0; i < 2*n; i++) {
            if (!dfn[i]) {
                tarjan(tarjan, i);
            }
        }

        bool invalid = false;
        for (int i = 0; i < n; i++) {
            if (scc[TRUE_BASE + i] == scc[FALSE_BASE + i]) {
                cout << "NO\n";
                invalid = true;
                break;
            }
        }

        if (invalid) {
            continue;
        }

        cout << "YES\n";
    }
}