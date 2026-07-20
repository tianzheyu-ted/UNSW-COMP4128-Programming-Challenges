
#include <set>
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    int n, e;
    cin >> n >> e;

    vector<int> in_degree(n + 1, 0);
    vector<vector<int>> adj(n + 1, vector<int>());

    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        in_degree[v]++;
    }

    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    int counter = 0;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        counter++;

        for (int v : adj[u]) {
            in_degree[v]--;
            if (in_degree[v] == 0) {
                q.push(v);
            }
        }
    }


    if (counter == n) {
        cout << "No Cycle\n";
    } else {
        cout << "Cycle\n";
    }

    return 0;
}