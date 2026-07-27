
#include <map>
#include <queue>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;


struct FlowNetwork {
    struct Edge {
        int v;
        long long cap;
        long long flow;
        int rev;
    };

    int n;
    const int INF = 1e9;
    vector<vector<Edge>> adjList;

    // level [v] stores dist from s to v
    // uptochild [v] stores first non - useless child.
    vector <int> level, uptochild ;

    FlowNetwork(int _n): n(_n) {
        adjList.resize(n);
        level.resize(n);
        uptochild.resize(n);
    }

    void add_edge (int u, int v, long long c) {
        adjList[u].push_back({v, c, 0, (int)adjList[v].size()});
        adjList[v].push_back({u, 0, 0, (int)adjList[u].size() - 1});
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        q.push(s);
        level[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            uptochild[u] = 0; 
            for (auto& edge : adjList[u]) {
                if (level[edge.v] == -1 && edge.cap - edge.flow > 0) { 
                    level[edge.v] = level[u] + 1;
                    q.push(edge.v);
                }
            }
        }
        return level[t] != -1;
    }

    long long augment(int u, int t, long long f) {
        if (u == t || f == 0) { return f; } 
        for (int &i = uptochild[u]; i < adjList[u].size(); i++) {
            Edge &edge = adjList[u][i];
            if (level[edge.v] == level[u] + 1 && edge.cap - edge.flow > 0) {
                long long rf = augment(edge.v, t, min(f, edge.cap - edge.flow));
                if (rf > 0) {
                    edge.flow += rf;
                    adjList[edge.v][edge.rev].flow -= rf;
                    return rf;
                }
            }
        }
        level[u] = -1;
        return 0;
    }

    long long dinic(int s, int t) {
        long long res = 0;
        while (bfs(s,t)) {
            while (long long x = augment(s, t, INF)) { res += x; }
        }
        return res;
    }
};


int main() {
    int n, t;
    cin >> n >> t;

    pair<int, int> broken_reactor;

    vector<string> scientists(n, "");
    for (int i = 0; i < n; i++) {
        cin >> scientists[i];
        for (int j = 0; j < n; j++) {
            if (scientists[i][j] == 'Z') {
                broken_reactor = {i, j};
            }
        }
    }

    int counter = 0;
    vector<pair<int, int>> rescue_capsules_list;
    map<pair<int, int>, int> rescue_capsules_map;
    vector<string> rescue_capsules(n, "");
    for (int i = 0; i < n; i++) {
        cin >> rescue_capsules[i];
        for (int j = 0; j < n; j++) {
            if ('0' <= rescue_capsules[i][j] && rescue_capsules[i][j] <= '9') {
                rescue_capsules_list.push_back({i, j});
                rescue_capsules_map[{i, j}] = counter;
                counter++;
            }
        }
    }

    vector<vector<int>> visited(n, vector<int>(n, 1e9));
    auto bfs = [&] (pair<int, int> src) {
        auto q = queue<pair<int, int>>();
        q.push(src);
        visited[src.first][src.second] = 0;
        while (!q.empty()) {
            auto curr = q.front(); q.pop();
            if (
                curr.first - 1 >= 0 
                && scientists[curr.first - 1][curr.second] != 'Y'
                && scientists[curr.first - 1][curr.second] != 'Z'
                && visited[curr.first - 1][curr.second] == 1e9
            ) {
                visited[curr.first - 1][curr.second] = visited[curr.first][curr.second] + 1;
                q.push({curr.first - 1, curr.second});
            }
            if (
                curr.first + 1 < n
                && scientists[curr.first + 1][curr.second] != 'Y'
                && scientists[curr.first + 1][curr.second] != 'Z'
                && visited[curr.first + 1][curr.second] == 1e9
            ) {
                visited[curr.first + 1][curr.second] = visited[curr.first][curr.second] + 1;
                q.push({curr.first + 1, curr.second});
            }
            if (
                curr.second - 1 >= 0 
                && scientists[curr.first][curr.second - 1] != 'Y'
                && scientists[curr.first][curr.second - 1] != 'Z'
                && visited[curr.first][curr.second - 1] == 1e9
            ) {
                visited[curr.first][curr.second - 1] = visited[curr.first][curr.second] + 1;
                q.push({curr.first, curr.second - 1});
            }
            if (
                curr.second + 1 < n
                && scientists[curr.first][curr.second + 1] != 'Y'
                && scientists[curr.first][curr.second + 1] != 'Z'
                && visited[curr.first][curr.second + 1] == 1e9
            ) {
                visited[curr.first][curr.second + 1] = visited[curr.first][curr.second] + 1;
                q.push({curr.first, curr.second + 1});
            }
        }
    };
    
    bfs(broken_reactor);

    // [0, n*n - 1]             : (i, j, 0)
    //     ...                  :    ...
    // [n*n*k, n*n*(k+1) - 1]   : (i, j, k)
    //     ...                  :    ...
    // [n*n*t, n*n*t+size()-1]  : capsules[i]
    // [n*n*t+size()]           : S
    // [n*n*t+size() + 1]       : T
    FlowNetwork network = FlowNetwork(n*n*(t+1) + rescue_capsules_map.size() + 2);

    auto get_node = [&](int r, int c, int time) {
        return time * n * n + r * n + c;
    };

    // S -> (i, j, 0)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ('0' <= scientists[i][j] && scientists[i][j] <= '9') {
                network.add_edge(
                    n*n*(t+1) + rescue_capsules_map.size(),
                    get_node(i, j, 0),
                    scientists[i][j] - '0'
                );
            }    
        }
    }
    
    for (int k = 1; k <= t; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (k - 1 >= visited[i][j]) continue;

                // (i, j, k-1) -> (i, j, k)
                if (k <= visited[i][j]) {
                    network.add_edge(
                        get_node(i, j, k - 1),
                        get_node(i, j, k), 
                        network.INF
                    );
                }
                
                // (i, j, k-1) -> (i - 1, j, k)
                if (
                    i - 1 >= 0 
                    && (scientists[i - 1][j] != 'Z' && scientists[i - 1][j] != 'Y')
                    && k <= visited[i - 1][j]
                ) {
                    network.add_edge(
                        get_node(i, j, k - 1), 
                        get_node(i - 1, j, k), 
                        network.INF
                    );
                }

                // (i, j, k-1) -> (i + 1, j, k)
                if (
                    i + 1 < n 
                    && (scientists[i + 1][j] != 'Z' && scientists[i + 1][j] != 'Y')
                    && k <= visited[i + 1][j]
                ) {
                    network.add_edge(
                        get_node(i, j, k - 1), 
                        get_node(i + 1, j, k), 
                        network.INF
                    );
                }

                // (i, j, k-1) -> (i, j - 1, k)
                if (
                    j - 1 >= 0 
                    && (scientists[i][j - 1] != 'Z' && scientists[i][j - 1] != 'Y')
                    && k <= visited[i][j - 1]
                ) {
                    network.add_edge(
                        get_node(i, j, k - 1), 
                        get_node(i, j - 1, k), 
                        network.INF
                    );
                }

                // (i, j, k-1) -> (i, j + 1, k)
                if (
                    j + 1 < n 
                    && (scientists[i][j + 1] != 'Z' && scientists[i][j + 1] != 'Y')
                    && k <= visited[i][j + 1]
                ) {
                    network.add_edge(
                        get_node(i, j, k - 1), 
                        get_node(i, j + 1, k), 
                        network.INF
                    );
                }

                if (rescue_capsules_map.count({i, j})) {
                    network.add_edge(
                        get_node(i, j, k - 1), 
                        n*n*(t+1) + rescue_capsules_map[{i, j}], 
                        network.INF
                    );

                    if (k == t || k == visited[i][j]) {
                        network.add_edge(
                            get_node(i, j, k), 
                            n*n*(t+1) + rescue_capsules_map[{i, j}], 
                            network.INF
                        );
                    }
                }
            }
        }
    }

    for (int i = 0; i < rescue_capsules_map.size(); i++) {
        network.add_edge(
            n*n*(t+1) + i, 
            n*n*(t+1) + rescue_capsules_map.size() + 1, 
            rescue_capsules[rescue_capsules_list[i].first][rescue_capsules_list[i].second] - '0'
        );
    }

    long long max_flow = network.dinic(
        n*n*(t+1) + rescue_capsules_map.size(), 
        n*n*(t+1) +rescue_capsules_map.size() + 1
    );

    cout << max_flow << '\n';
}