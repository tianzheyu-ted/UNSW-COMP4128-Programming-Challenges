
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
        adj[v].push_back(u);
    }

    int timer = 0;
    vector<int> tin(n + 1, 0);
    vector<int> low(n + 1, 0);
    vector<pair<int, int>> bridges;

    auto dfs = [&] (auto& self, int curr, int parent) -> void {
        timer++;
        tin[curr] = timer;
        low[curr] = timer;
        for (int next : adj[curr]) {
            if (next == parent) continue;
            if (!tin[next]) {
                self(self, next, curr);
                low[curr] = min(low[curr], low[next]);
                if (low[next] > tin[curr]) {
                    bridges.push_back({curr, next});
                }
            } else {
                low[curr] = min(low[curr], tin[next]);
            }
        }
    };

    dfs(dfs, 1, 0);

    for (auto bridge : bridges) {
        cout << bridge.first << ' ' << bridge.second << '\n';
    }
}