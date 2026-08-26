
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<vector<int>> adj(1 + n, vector<int>(1 + n, -1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> adj[i][j];
        }
    }

    vector<int> deleted(n, -1);
    for (int i = 0; i < n; i++) {
        cin >> deleted[i];
    }

    reverse(deleted.begin(), deleted.end());

    vector<vector<int>> dist(n + 1, vector<int>(n + 1, 1e8));

    for (int i = 1; i <= n; i++) dist[i][i] = 0;
    
    for (int u = 1; u <= n; u++) {
        for (int i = 1; i <= n; i++) {
            dist[u][i] = min(dist[u][i], adj[u][i]);
        }       
    }


    vector<long long> results;
    results.reserve(n);

    set<int> in_graph;

    for (auto mid : deleted) {
        in_graph.insert(mid);

        for (int start = 1; start <= n; start++) {
            for (int end = 1; end <= n; end++) {
                if (dist[start][mid] < 1e8 && dist[mid][end] < 1e8) {
                    if (dist[start][mid] + dist[mid][end] < dist[start][end]) {
                        dist[start][end] = dist[start][mid] + dist[mid][end];
                    }
                }
            }
        }

        long long result = 0;
        for (int start : in_graph) {
            for (int end : in_graph) {
                if (start != end) {
                    result += dist[start][end];
                }
            }
        }

        results.push_back(result);
    }

    reverse(results.begin(), results.end());

    for (auto result : results) {
        cout << result << ' ';
    }

    cout << '\n';
}