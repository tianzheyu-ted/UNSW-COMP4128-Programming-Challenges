
#include <set>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a - 1].push_back(b - 1);
        adj[b - 1].push_back(a - 1);
    }

    int timer = 0;
    vector<int> tin(n, 0);
    vector<int> low(n, 0);
    vector<pair<int, int>> bridges;
    set<pair<int, int>> directed_edges;

    auto dfs = [&] (auto& self, int src, int parent) -> void {
        timer++;
        tin[src] = timer;
        low[src] = timer;
        for (auto& next : adj[src]) {
            if (next != parent) {
                if (!tin[next]) {
                    // Tree Edge: to new vertex
                    self(self, next, src);
                    low[src] = min(low[src], low[next]);
                    if (low[next] > tin[src]) {
                        bridges.push_back({src, next});
                    }
                    directed_edges.insert({src + 1, next + 1});
                } else if (tin[next] < tin[src]) {
                    // Back Edge: to ancestor vertex
                    low[src] = min(low[src], tin[next]);
                    directed_edges.insert({src + 1, next + 1});
                } else {
                    // Forward/Cross Edge: to descendant vertex
                }
            }
        }
    };

    dfs(dfs, 0, -1);

    if (bridges.size() > 0) {
        cout << 0 << '\n';
        return 0;
    }

    for (auto edge : directed_edges) {
        cout << edge.first << ' ' << edge.second << '\n';
    }
}