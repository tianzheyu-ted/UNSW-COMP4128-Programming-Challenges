
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<vector<int>> adj(n + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> adj[i][j];
        }
    }
    
    vector<int> deleted_vertices(n, -1);
    for (int i = 0; i < n; i++) {
        cin >> deleted_vertices[i];
    }

    reverse(deleted_vertices.begin(), deleted_vertices.end());
    
    vector<vector<long long>> dist(n + 1, vector<long long>(n + 1, 1e18));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dist[i][j] = adj[i][j];
        }
    }

    vector<long long> results;
    results.reserve(n);

    set<int> in_graph;
    for (auto mid : deleted_vertices) {
        in_graph.insert(mid);
        for (int src = 1; src <= n; src++) {
            for (int dest = 1; dest <= n; dest++) {
                dist[src][dest] = min(dist[src][mid] + dist[mid][dest], dist[src][dest]);
            }
        }

        long long result = 0;
        for (int src : in_graph) {
            for (int dest: in_graph) {
                result += dist[src][dest];
            }
        }

        results.push_back(result);
    }

    reverse(results.begin(), results.end());

    for (auto item : results) {
        cout << item << ' ';
    }

    cout << '\n';
}