
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

    auto tarjan_bridge = [] (vector<vector<int>>& adj) -> vector<pair<int, int>> {
        int timer = 0;
        int n = adj.size();
        vector<int> tin(n, 0);
        vector<int> low(n, 0);
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
        for (int i = 0; i < n; i++) {
            if (!tin[i]) {
                dfs(dfs, i, -1); 
            }
        }
        return bridges;
    };

    auto bridges = tarjan_bridge(adj);

    for (auto bridge : bridges) {
        cout << bridge.first << ' ' << bridge.second << '\n';
    }
}