
#include <set>
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

struct Edge {
    int id;
    int to;
    char type;
    long long length;
};

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<Edge>> adj(n + 1, vector<Edge>());
    for (int i = 0; i < m; i++) {
        int u, v, x;
        cin >> u >> v >> x;
        adj[u].push_back({i, v, 'R', x});
        adj[v].push_back({i, u, 'R', x});
    }

    vector<Edge> train_routes(k, {-1, -1, 'T', -1});
    for (int i = 0; i < k; i++) {
        int s, y;
        cin >> s >> y;
        adj[1].push_back({m + i, s, 'T', y});
        adj[s].push_back({m + i, 1, 'T', y});
        train_routes[i] = {m + i, s, 'T', y};
    }

    vector<int> ways(n + 1, 0);

    vector<long long> distances(n + 1, 1e18);
    distances[1] = 0;

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({0, 1});
    
    while (pq.size() > 0) {
        auto curr = pq.top();
        pq.pop();

        if (curr.first > distances[curr.second]) continue;

        for (auto edge : adj[curr.second]) {
            if (curr.first + edge.length < distances[edge.to]) {
                distances[edge.to] = curr.first + edge.length;
                pq.push({curr.first + edge.length, edge.to});
                ways[edge.to] = 1;
            } else if (curr.first + edge.length == distances[edge.to]) {
                ways[edge.to]++;
            }
        }
    }

    int result = 0;
    for (auto train_route : train_routes) {
        int city = train_route.to;
        if (train_route.length > distances[city]) {
            result++;
        } else if (train_route.length == distances[city]) {
            if (ways[city] > 1) {
                result++;
                ways[city]--;
            }
        }
    }

    cout << result << '\n';
}