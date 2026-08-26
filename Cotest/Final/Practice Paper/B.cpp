
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

int main() {
    int n, p, f;
    cin >> n >> p >> f;

    vector<vector<int>> adj1(n + p + 1, vector<int>());
    for (int i = 0; i < p; i++) {
        int a;
        cin >> a;
        for (int j = 0; j < a; j++) {
            int b;
            cin >> b;
            adj1[b].push_back(n + 1 + i);
            adj1[n + 1 + i].push_back(b);
        }
    }

    vector<vector<int>> adj2(n + f + 1, vector<int>());
    for (int i = 0; i < f; i++) {
        int c;
        cin >> c;
        for (int j = 0; j < c; j++) {
            int d;
            cin >> d;
            adj2[d].push_back(n + 1 + i);
            adj2[n + 1 + i].push_back(d);
        }
    }

    auto bfs = [] (int start, int total_nodes, vector<vector<int>>& adj) -> vector<int> {
        vector<int> dist(total_nodes, -1);
        queue<int> q;
        dist[start] = 0;
        q.push(start);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        return dist;
    };

    vector<int> dist_erdos = bfs(1, n + p + 1, adj1);
    vector<int> dist_bacon = bfs(n, n + f + 1, adj2);

    for (int i = 1; i <= n; i++) {
        if (dist_erdos[i] == -1 || dist_bacon[i] == -1) {
            cout << "INF" << (i == n ? "" : " ");
        } else {
            int erdos_num = dist_erdos[i] / 2;
            int bacon_num = dist_bacon[i] / 2;
            cout << (erdos_num + bacon_num) << (i == n ? "" : " ");
        }
    }
    cout << "\n";

    return 0;
}